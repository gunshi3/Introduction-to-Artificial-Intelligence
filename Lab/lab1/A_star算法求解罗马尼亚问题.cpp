#include <iostream>
#include <vector>
#include <memory.h>
#include <stack>
#include <algorithm>

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define L 9
#define M 10
#define N 11
#define O 12
#define P 13
#define R 14
#define S 15
#define T 16
#define U 17
#define V 18
#define Z 19

using namespace std;

/*
*从n节点到目标节点可能的最优路径的估计代价
*/
int h[20] =
    {366, 0, 160, 242, 161,
     178, 77, 151, 226, 244,
     241, 234, 380, 98, 193,
     253, 329, 80, 199, 374};

/*
*一个节点结构，node
*/
struct node
{
    int g; //从起始节点到n节点的已走过路径的实际代价
    int h; //从n节点到目标节点可能的最优路径的估计代价
    int f; //代价估计函数
    int name;
    node(int name, int g, int h)
    { //构造函数
        this->name = name;
        this->g = g;
        this->h = h;
        this->f = g + h;
    };

    //重载运算符
    bool operator<(const node &a) const { return f < a.f; }
};

class Graph //图结构
{
public:
    Graph()
    {
        memset(graph, -1, sizeof(graph)); //图初始化为-1
    }

    int getEdge(int from, int to)
    { //获取边
        return graph[from][to];
    }

    void addEdge(int from, int to, int cost)
    { //新增一条边
        if (from >= 20 || from < 0 || to >= 20 || to < 0)
            return;
        graph[from][to] = cost;
    }

    void init()
    { //图初始化
        addEdge(O, Z, 71);
        addEdge(Z, O, 71);

        addEdge(O, S, 151);
        addEdge(S, O, 151);

        addEdge(Z, A, 75);
        addEdge(A, Z, 75);

        addEdge(A, S, 140);
        addEdge(S, A, 140);

        addEdge(A, T, 118);
        addEdge(T, A, 118);

        addEdge(T, L, 111);
        addEdge(L, T, 111);

        addEdge(L, M, 70);
        addEdge(M, L, 70);

        addEdge(M, D, 75);
        addEdge(D, M, 75);

        addEdge(D, C, 120);
        addEdge(C, D, 120);

        addEdge(C, R, 146);
        addEdge(R, C, 146);

        addEdge(S, R, 80);
        addEdge(R, S, 80);

        addEdge(S, F, 99);
        addEdge(F, S, 99);

        addEdge(F, B, 211);
        addEdge(B, F, 211);

        addEdge(P, C, 138);
        addEdge(C, P, 138);

        addEdge(R, P, 97);
        addEdge(P, R, 97);

        addEdge(P, B, 101);
        addEdge(B, P, 101);

        addEdge(B, G, 90);
        addEdge(G, B, 90);

        addEdge(B, U, 85);
        addEdge(U, B, 85);

        addEdge(U, H, 98);
        addEdge(H, U, 98);

        addEdge(H, E, 86);
        addEdge(E, H, 86);

        addEdge(U, V, 142);
        addEdge(V, U, 142);

        addEdge(I, V, 92);
        addEdge(V, I, 92);

        addEdge(I, N, 87);
        addEdge(N, I, 87);
    }

private:
    int graph[20][20]; //图数组，用来保存图信息，最多有20个节点
};

bool list[20];         //用于记录节点i是否在openlist集合中
vector<node> openList; //扩展节点集合
bool closeList[20];    //可访问集合
stack<int> road;       //路径
int parent[20];        //父节点

void A_star(int goal, node &src, Graph &graph)
{
    openList.push_back(src);
    sort(openList.begin(), openList.end()); //排序

    while (!openList.empty())
    {
        /*取代价最小的节点*/
        node cur = openList[0]; //取首节点，代价最小
        if (cur.name == goal)   //目标
            return;
        openList.erase(openList.begin()); //从openlist序列中删除这个节点
        list[cur.name] = false;           //将当前节点标记为不在openList中
        closeList[cur.name] = true;       //将当前节点加入closeList

        /*遍历子节点*/
        for (int i = 0; i < 20; i++)
        {
            if (graph.getEdge(cur.name, i) != -1 && !closeList[i]) //节点相邻并且不在close中，可访问
            {
                if (list[i]) //如果在list序列中，说明属于扩展节点集
                {
                    int j = 0;
                    for (int j = 0; j < openList.size(); j++)
                    { //遍历，找到当前节点的位置
                        if (openList[j].name == i)
                            break;
                    }
                    /*刷新节点*/
                    if (cur.g + graph.getEdge(cur.name, i) < openList[j].g)
                    {
                        openList[j].g = cur.g + graph.getEdge(cur.name, i); //更新g
                        openList[j].f = openList[j].g + openList[j].h;      //更新f
                        sort(openList.begin(), openList.end());             //排序
                        parent[i] = cur.name;                               //更新parent
                    }
                }
                else //节点不在openList，则创建一个新点，加入openList扩展集
                {
                    node newNode(i, cur.g + graph.getEdge(cur.name, i), h[i]);
                    parent[i] = cur.name;
                    openList.push_back(newNode);
                    sort(openList.begin(), openList.end()); //排序
                    list[i] = true;
                }
            }
        }
    }
}

void print_result(Graph &graph)
{
    int p = openList[0].name;
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
        cout << road.top() << "-> ";
        if (road.top() != lastNodeNum)
        {
            cost += graph.getEdge(lastNodeNum, road.top());
            lastNodeNum = road.top();
        }
        road.pop();
    }
    cout << "end" << endl;
    cout << "cost:" << cost;
}
int main()
{
    Graph graph;
    graph.init();
    int goal = B;
    node src(A, 0, h[A]);
    list[A] = true;
    memset(parent, -1, sizeof(parent));
    memset(list, false, sizeof(list));
    A_star(goal, src, graph);
    print_result(graph);
    return 0;
}
