# DFS.cpp

```c++
#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

stack<int> road;     //·��
bool closeList[100]; //���ڼ�¼�Ƿ��߹�
int parent[100];     //���ڵ�

//�������
bool DFS(int cur, int endId, Graph &graph)
{
    if (cur == endId)
        return true;
    else
    {
        for (int i = 0; i < graph.getSize(); i++)
        {
            if (graph.getEdge(cur, i) != -1 && !closeList[i])
            {                        //��ǰ�ڵ����ڲ�����̽�������У���չ�ýڵ�
                closeList[i] = true; //���Ϊ�Ѿ�����
                parent[i] = cur;     //��¼��ǰ�ڵ�
                if (DFS(i, endId, graph))
                    return true;
                closeList[i] = false;
                parent[i] = -1; //���ø��ڵ�
            }
        }
    }
    return false;
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
    memset(closeList, false, sizeof(closeList));
    int startId = graph.getId(startCity), endId = graph.getId(endCity);
    closeList[startId] = true; //��ʾ�Ѿ�����
    Timer.Start();
    DFS(startId, endId, graph);
    Timer.End();
    double t = Timer.getTime();
    cout << startCity << ' ' << endCity << endl;
    print_result(graph, endId);
    cout << "time: " << t << "��s" << endl;
    return 0;
}
```
