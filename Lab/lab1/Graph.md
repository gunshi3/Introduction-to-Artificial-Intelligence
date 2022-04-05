# Graph.h

```cpp
#include <iostream>
#include <memory.h>
#include <map>
#include <fstream>
using namespace std;
string startCity, endCity;

class Graph //ͼ�ṹ
{
public:
    Graph()
    {
        memset(graph, -1, sizeof(graph)); //ͼ��ʼ��Ϊ-1
    }

    string getName(int id)
    { //��ȡ�ڵ���
        return city[id];
    }

    int getEdge(int from, int to)
    { //��ȡ��
        return graph[from][to];
    }

    void addEdge(int from, int to, int cost)
    { //����һ����
        if (from >= 20 || from < 0 || to >= 20 || to < 0)
            return;
        graph[from][to] = cost;
    }
    int getSize() { return size; } //��ȡͼ�Ĺ�ģ

    int getedgeN() { return edgeN; } //��ȡͼ�ı���

    int getH(int i) { return h[i]; } //��ȡ��ǰ�ڵ��H����ֵ

    int getId(string city) { return idMap[city]; }

    void getInfo()
    { //��ȡ�ļ���Ϣ
        string info;
        ifstream in("graphInfo.txt"); //��ȡ�ļ�

        //��ȡ��������
        in >> info;
        // cout << info << endl;
        in >> size;
        for (int i = 0; i < size; i++)
        {
            in >> city[i];
            idMap[city[i]] = i; //����ӳ��
        }

        //��ȡh����ֵ����
        in >> info;
        // cout << info << endl;
        for (int i = 0; i < size; i++)
        {
            in >> h[i];
        }

        //��ȡͼ�ڵ�
        in >> info;
        // cout << info << endl;
        in >> edgeN;
        for (int i = 0; i < edgeN; i++)
        {
            string u, v;
            int c;
            in >> u >> v >> c;
            addEdge(idMap[u], idMap[v], c);
        }

        //��ȡ��ʼ�ͽ�������
        in >> info;
        // cout << info << endl;
        in >> startCity >> endCity;
        in.close(); //�ر��ļ���
    }

    void init()
    { //ͼ��ʼ��
        getInfo();
    }

private:
    int graph[100][100];    //ͼ���飬��������ͼ��Ϣ�������20���ڵ�
    string city[100];       //Name���飬����id�ͽڵ�����ӳ��
    map<string, int> idMap; //�������ֵ�id��ӳ��
    int size;               //ͼ�Ĺ�ģ�ڵ���Ŀ
    int edgeN;              //�ߵ���Ŀ
    int h[100];             //��n�ڵ㵽Ŀ��ڵ���ܵ�����·���Ĺ��ƴ���
};
```
