# IDS.cpp

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
    int depth;    //��¼��ǰ�ڵ�Ĳ�
    Node *parent; //���ڵ�
    Node(int ii = 0, int dd = 0, Node *pp = NULL) : id(ii), depth(dd), parent(pp) {}
};

Node *root = NULL, *cur = NULL; //����������������IDS���̵Ľڵ���Ϣ
stack<Node *> st;               //ջ
bool closeList[100];            //�ɷ��ʼ���,true��ʾ�Ѿ�����

//��������������������
void IDS(int startId, int endId, int maxDep, Graph &graph)
{
    root = new Node(startId, 0, NULL);
    closeList[startId] = true;
    st.push(root);
    if (startId == endId)
        return;
    else
    {
        while (!st.empty())
        {
            cur = st.top();
            st.pop();
            if (cur->id == endId)
                return; //����Ŀ��
            for (int i = 0; i < graph.getSize(); i++)
            {
                if (graph.getEdge(i, cur->id) != -1 && closeList[i] != true && cur->depth < maxDep)
                {                                              //��ǰ�ڵ���Է���
                    st.push(new Node(i, cur->depth + 1, cur)); //����ǰ�ڵ���뼯��
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

    int i = 0;
    Timer.Start();
    for (i = 0; i < graph.getSize(); i++)
    {
        memset(closeList, false, sizeof(closeList));

        IDS(startId, endId, i, graph);

        if (cur->id == endId)
        {
            break;
        }
    }
    Timer.End();
    double t = Timer.getTime();
    cout << startCity << ' ' << endCity << endl;
    cout << "min_depth:" << i << endl;
    cout << "solution: ";
    print_result(graph, cur);
    cout << "end" << endl;
    cout << "cost:" << cost << endl;
    cout << "time: " << t << "��s" << endl;
    return 0;
}
```
