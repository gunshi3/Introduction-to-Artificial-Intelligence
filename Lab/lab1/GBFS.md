# GBFS.cpp

```c++
#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int id;       //��¼��ǰ�ڵ�����
    int f;        //�ڵ�Ĵ��ۺ���
    Node *parent; //���ڵ�
    Node(int ii = 0, int ff = 0, Node *pp = NULL) : id(ii), f(ff), parent(pp) {}
    //bool operator <(const Node &a)const {return f > a.f;}
};

struct cmp
{
    bool operator()(const Node *a, const Node *b)
    {
        return a->f > b->f;
    }
};

Node *root = NULL, *cur = NULL; //����������������IDS���̵Ľڵ���Ϣ
priority_queue<Node *, vector<Node *>, cmp> que;
bool closeList[100]; //�ɷ��ʼ���,true��ʾ�Ѿ�����

//̰���������
void GBFS(int startId, int endId, Graph &graph)
{
    closeList[startId] = true;
    root = new Node(startId, graph.getH(startId), NULL);
    que.push(root);
    if (startId == endId)
        return;
    else
    {
        while (!que.empty())
        {
            cur = que.top();
            que.pop();
            if (cur->id == endId)
                return; //����Ŀ��
            for (int i = 0; i < graph.getSize(); i++)
            {
                if (graph.getEdge(i, cur->id) != -1 && closeList[i] != true)
                {                                              //��ǰ�ڵ���Է���
                    que.push(new Node(i, graph.getH(i), cur)); //����ǰ�ڵ���뼯��
                    closeList[i] = true;
                }
            }
        }
    }
    return;
}

int cost = 0;
/*��ӡ�ӽڵ�*/
void print_result(Graph &graph, Node *cur)
{
    if (cur->parent == NULL)
    { //������ڵ�
        cout << graph.getName(cur->id) << "-> ";
        return;
    }
    //�ݹ鴦��
    cost += graph.getEdge(cur->id, (cur->parent)->id);
    print_result(graph, cur->parent);
    cout << graph.getName(cur->id) << "-> ";
}
int main()
{
    Graph graph;  //ͼ��
    graph.init(); //��Ϣ��ʼ��
    memset(closeList, false, sizeof(closeList));
    int startId = graph.getId(startCity), endId = graph.getId(endCity);

    Timer.Start();
    GBFS(startId, endId, graph);
    Timer.End();
    double t = Timer.getTime();
    cout << startCity << ' ' << endCity << endl;
    cout << "solution: ";
    print_result(graph, cur);
    cout << "end" << endl;
    cout << "cost:" << cost << endl;
    cout << "time: " << t << "��s" << endl;
    return 0;
}
```
