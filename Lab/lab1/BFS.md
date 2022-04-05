# BFS.cpp

```c++
#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int id;    //��¼��ǰ�ڵ�����
    int level; //��¼��ǰ�ڵ�Ĳ�
    Node(int ii = 0, int ll = 0) : id(ii), level(ll) {}
};

queue<Node> que;       //����
bool closeList[100];   //�ɷ��ʼ���,true��ʾ�Ѿ�����
stack<int> road;       //·��
int levels[100] = {0}; //�ڵ��¼��

//�����������
void BFS(int startId, int endId, Graph &graph)
{
    closeList[startId] = true; //��ʾ�Ѿ�����
    if (startId == endId)
        return;
    else
    {
        levels[startId] = 0;
        que.push(Node(startId, 0));
        while (!que.empty())
        {
            Node q = que.front(); //ȡ���ӽڵ㣬��չ
            que.pop();
            int id = q.id, level = q.level;
            if (id == endId)
                return; //����Ŀ��ڵ�
            for (int i = 0; i < graph.getSize(); i++)
            {
                if (graph.getEdge(id, i) != -1 && !closeList[i])
                { //��ǰ�ڵ������ҿɷ���
                    closeList[i] = true;
                    levels[i] = level + 1;
                    que.push(Node(i, level + 1));
                }
            }
        }
    }
    return;
}

/*��ӡ�ӽڵ�*/
void print_result(Graph &graph, int endId)
{
    int p = endId;
    int lastNodeNum;
    while (levels[p] != 0)
    {
        road.push(p);
        for (int i = 0; i < graph.getSize(); i++)
        {
            if (levels[i] == (levels[p] - 1) && graph.getEdge(p, i) != -1)
            { //�ҵ��˸��ڵ�
                p = i;
                break;
            }
        }
    }
    road.push(p);
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
    Graph graph;                        //ͼ��
    graph.init();                       //��Ϣ��ʼ��
    memset(levels, -1, sizeof(levels)); //��ʼ��levels
    memset(closeList, false, sizeof(closeList));
    int startId = graph.getId(startCity), endId = graph.getId(endCity);
    Timer.Start();
    BFS(startId, endId, graph);
    Timer.End();
    double t = Timer.getTime();
    cout << startCity << ' ' << endCity << endl;
    print_result(graph, endId);
    cout << "time: " << t << "��s" << endl;
    return 0;
}
```
