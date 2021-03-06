#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct node //一个节点结构，node
{
    int g;  //从起始节点到n节点的已走过路径的实际代价
    int h;  //从n节点到目标节点可能的最优路径的估计代价
    int f;  //代价估计函数
    int id; //当前节点的id
    node(int id = 0, int g = 0, int h = 0)
    { //构造函数
        this->id = id;
        this->g = g;
        this->h = h;
        this->f = g + h;
    };
    //重载运算符
    bool operator<(const node &a) const { return f < a.f; }
};

bool list[20];         //用于记录是否走过
vector<node> openList; //扩展节点集合
bool closeList[20];    //可访问集合
stack<int> road;       //路径
int parent[20];        //父节点

void A_star(int endId, node &src, Graph &graph)
{
    openList.push_back(src);
    sort(openList.begin(), openList.end());

    while (!openList.empty())
    {
        /*取代价最小的节点*/
        node cur = openList[0]; //取首节点，代价最小
        if (cur.id == endId)    //目标
            return;
        openList.erase(openList.begin()); //从openlist序列中删除这个节点
        list[cur.id] = false;             //将当前节点标记为不在openList中
        closeList[cur.id] = true;         //将当前节点加入closeList
        /*遍历子节点*/
        for (int i = 0; i < graph.getSize(); i++)
        {
            if (graph.getEdge(cur.id, i) != -1 && !closeList[i]) //节点相邻并且不在close中，可访问
            {
                if (list[i]) //如果在list序列中，说明属于扩展节点集
                {
                    unsigned int j = 0;
                    for (j = 0; j < openList.size(); j++)
                    { //遍历，找到当前节点的位置
                        if (openList[j].id == i)
                            break;
                    }
                    /*刷新节点*/
                    int cost = cur.g + graph.getEdge(cur.id, i);
                    if (cost < openList[j].g)
                    {
                        openList[j].g = cost;                 //更新g
                        openList[j].f = cost + openList[j].h; //更新f
                        parent[i] = cur.id;                   //更新parent
                    }
                }
                else //节点不在openList，则创建一个新点，加入openList扩展集
                {
                    node newNode(i, cur.g + graph.getEdge(cur.id, i), graph.getH(i));
                    parent[i] = cur.id;
                    openList.push_back(newNode);
                    sort(openList.begin(), openList.end()); //排序
                    list[i] = true;
                }
            }
        }
    }
}
void print_result(Graph &graph, int endId)
{
    int p = endId;
    int lastNodeNum;
    road.push(p);
    while (parent[p] != -1)
    {
        road.push(parent[p]);
        p = parent[p];
    }
    lastNodeNum = road.top();
    int cost = 0;
    cout << "solution: ";
    while (!road.empty())
    {
        cout << graph.getName(road.top()) << "-> ";
        if (road.top() != lastNodeNum)
        {
            cost += graph.getEdge(lastNodeNum, road.top());
            lastNodeNum = road.top();
        }
        road.pop();
    }
    cout << "end" << endl;
    cout << "cost:" << cost << endl;
}

int main()
{
    Graph graph;                         //图类clear
    graph.init();                        //信息初始化
    list[graph.getId(startCity)] = true; //
    memset(parent, -1, sizeof(parent));
    memset(list, false, sizeof(list));
    int startId = graph.getId(startCity), endId = graph.getId(endCity);
    node src(startId, 0, graph.getH(startId));
    cout << startCity << ' ' << endCity << endl;
    Timer.Start();
    A_star(endId, src, graph);
    Timer.End();
    double t = Timer.getTime();
    print_result(graph, endId);
    cout << "time: " << t << "μs" << endl;
    return 0;
}
