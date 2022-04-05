# AStar.cpp

```c++
#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct node //һ���ڵ�ṹ��node
{
    int g;  //����ʼ�ڵ㵽n�ڵ�����߹�·����ʵ�ʴ���
    int h;  //��n�ڵ㵽Ŀ��ڵ���ܵ�����·���Ĺ��ƴ���
    int f;  //���۹��ƺ���
    int id; //��ǰ�ڵ��id
    node(int id = 0, int g = 0, int h = 0)
    { //���캯��
        this->id = id;
        this->g = g;
        this->h = h;
        this->f = g + h;
    };
    //���������
    bool operator<(const node &a) const { return f < a.f; }
};

bool list[20];         //���ڼ�¼�Ƿ��߹�
vector<node> openList; //��չ�ڵ㼯��
bool closeList[20];    //�ɷ��ʼ���
stack<int> road;       //·��
int parent[20];        //���ڵ�

void A_star(int endId, node &src, Graph &graph)
{
    openList.push_back(src);
    sort(openList.begin(), openList.end());

    while (!openList.empty())
    {
        /*ȡ������С�Ľڵ�*/
        node cur = openList[0]; //ȡ�׽ڵ㣬������С
        if (cur.id == endId)    //Ŀ��
            return;
        openList.erase(openList.begin()); //��openlist������ɾ������ڵ�
        list[cur.id] = false;             //����ǰ�ڵ���Ϊ����openList��
        closeList[cur.id] = true;         //����ǰ�ڵ����closeList
        /*�����ӽڵ�*/
        for (int i = 0; i < graph.getSize(); i++)
        {
            if (graph.getEdge(cur.id, i) != -1 && !closeList[i]) //�ڵ����ڲ��Ҳ���close�У��ɷ���
            {
                if (list[i]) //�����list�����У�˵��������չ�ڵ㼯
                {
                    unsigned int j = 0;
                    for (j = 0; j < openList.size(); j++)
                    { //�������ҵ���ǰ�ڵ��λ��
                        if (openList[j].id == i)
                            break;
                    }
                    /*ˢ�½ڵ�*/
                    int cost = cur.g + graph.getEdge(cur.id, i);
                    if (cost < openList[j].g)
                    {
                        openList[j].g = cost;                 //����g
                        openList[j].f = cost + openList[j].h; //����f
                        parent[i] = cur.id;                   //����parent
                    }
                }
                else //�ڵ㲻��openList���򴴽�һ���µ㣬����openList��չ��
                {
                    node newNode(i, cur.g + graph.getEdge(cur.id, i), graph.getH(i));
                    parent[i] = cur.id;
                    openList.push_back(newNode);
                    sort(openList.begin(), openList.end()); //����
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
    Graph graph;                         //ͼ��clear
    graph.init();                        //��Ϣ��ʼ��
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
    cout << "time: " << t << "��s" << endl;
    return 0;
}
```
