# UCS.cpp

```c++
#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node //һ���ڵ�ṹ��node
{
    int g;  //����ʼ�ڵ㵽n�ڵ�����߹�·����ʵ�ʴ���
    int f;  //���۹��ƺ���
    int id; //��ǰ�ڵ��id
    node(int id = 0, int g = 0)
    { //���캯��
        this->id = id;
        this->g = g;
        this->f = g;
    };
    //���������
    bool operator<(const node &a) const { return f < a.f; }
};

bool list[100];        //���ڼ�¼�Ƿ��߹�
vector<node> frontier; //��չ�ڵ㼯��
bool explored[100];    //�ɷ��ʼ���
stack<int> road;       //·��
int parent[100];       //���ڵ�

void UCS(int endCity, node &src, Graph &graph)
{
    frontier.push_back(src);
    sort(frontier.begin(), frontier.end());
    while (!frontier.empty())
    {
        /*ȡ������С�Ľڵ�*/
        node cur = frontier[0]; //ȡ�׽ڵ㣬������С
        if (cur.id == endCity)  //Ŀ��
            return;
        frontier.erase(frontier.begin()); //��openlist������ɾ������ڵ�
        list[cur.id] = false;             //����ǰ�ڵ���Ϊ����openList��
        explored[cur.id] = true;          //����ǰ�ڵ����closeList
        /*�����ӽڵ�*/
        for (int i = 0; i < graph.getSize(); i++)
        {
            if (graph.getEdge(cur.id, i) != -1 && !explored[i]) //�ڵ����ڲ��Ҳ���explored�У��ɷ���
            {
                if (list[i]) //�����list�����У�˵��������չ�ڵ㼯
                {
                    unsigned int j = 0;
                    for (j = 0; j < frontier.size(); j++)
                    { //�������ҵ���ǰ�ڵ��λ��
                        if (frontier[j].id == i)
                            break;
                    }
                    /*ˢ�½ڵ�*/
                    int cost = cur.g + graph.getEdge(cur.id, i);
                    if (cost < frontier[j].g)
                    {
                        frontier[j].g = cost; //����g
                        frontier[j].f = cost; //����f
                        parent[i] = cur.id;   //����parent
                    }
                }
                else //�ڵ㲻��openList���򴴽�һ���µ㣬����openList��չ��
                {
                    node newNode(i, cur.g + graph.getEdge(cur.id, i));
                    parent[i] = cur.id;
                    frontier.push_back(newNode);
                    sort(frontier.begin(), frontier.end()); //����
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
    Graph graph;  //ͼ��
    graph.init(); //��Ϣ��ʼ��
    memset(parent, -1, sizeof(parent));
    memset(list, false, sizeof(list));
    int startId = graph.getId(startCity), endId = graph.getId(endCity);
    node src(startId, 0);
    list[graph.getId(startCity)] = true;

    Timer.Start();
    UCS(endId, src, graph); //UCS����
    Timer.End();
    double t = Timer.getTime();
    cout << startCity << ' ' << endCity << endl;
    print_result(graph, endId);
    cout << "time: " << t << "��s" << endl;
    return 0;
}
```
