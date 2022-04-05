# 人工智能导论实验1说明文档

## 一、目录结构

```shell
$ lab1
.
├── AStar.cpp
├── BFS.cpp
├── DFS.cpp
├── GBFS.cpp
├── Graph.h
├── graphInfo.txt
├── IDS.cpp
├── Timer.h
└── UCS.cpp
```

- `Graph.h`：图类，用于记录图的信息
- `Timer.h`：时间测试类，用于方便的对运行程序进行时间测试
- `graphInfo.txt`：图信息输入文本

- `BFS.cpp`：广度优先搜索
- `DFS.cpp`：深度优先搜索
- `IDS.cpp`：迭代加深搜索
- `UCS.cpp`：一致性代价搜索
- `GBFS.cpp`：贪婪最佳优先搜索
- `AStart.cpp`：A*搜索

## 二、环境

- `操作系统`：Windows 10 专业版  

- `开发语言`：C++ Python  
- `编译器`：VScode Pycharm

## 三、算法说明

### （1）广度优先搜索BFS

```cpp
#include "Graph.h"
#include "Timer.h"
#include <iostream>
#include <queue>
using namespace std;
struct Node{}                       //节点

queue<Node>que;                     //队列
bool closeList[100];                //可访问集合,true表示已经访问
stack<int> road;                    //路径
int levels[100]={0};                //节点记录层

//宽度优先搜索
void BFS(int startId,int endId,Graph &graph){}

/*打印子节点*/
void print_result(Graph &graph,int endId){}

int main(){}
```

- 程序说明

程序BFS.cpp主要包含了4个模块，其中`struct Node{}`定义了搜索过程的节点，`void BFS(int startId,int endId,Graph &graph){}` 是我实现BFS算法主体，`void print_result(Graph &graph,int endId){}`用于根据搜索的结果打印一条路径。`mian()`则是程序执行入口。

- [代码](https://1541453904.rth1.me/BFS.html)（可点击，下同）

### （2）深度优先搜索DFS

```cpp
#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

stack<int> road;                            //路径
bool closeList[100];                        //用于记录是否走过
int parent[100];                            //父节点


bool DFS(int cur,int endId,Graph &graph){}  //深度优先搜索

void print_result(Graph &graph,int endId){} //打印

int main(){}                                //主函数

```

- 程序说明

程序DFS.cpp主要包含了4个模块，其中`stack<int>road`定义了搜索的路径，`void DFS(int startId,int endId,Graph &graph){}` 是我实现DFS算法主体，`void print_result(Graph &graph,int endId){}`用于根据搜索的结果打印一条路径。`mian()`则是程序执行入口。

- [代码](https://1541453904.rth1.me/DFS.html)

### （3）迭代加深搜索IDS

```cpp
#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <iostream>
#include <queue>
using namespace std;
struct Node{}                           //记录节点
Node *root=NULL,*cur=NULL;              //创建树，用来保存IDS过程的节点信息
stack<Node*>st;                         //栈
bool closeList[100];                    //可访问集合,true表示已经访问


void IDS(int startId,int endId,int maxDep,Graph &graph){} //迭代加深的深度优先搜索

void print_result(Graph &graph,Node * cur){} //打印子节点

int main(){}
```

- 程序说明

程序DFS.cpp主要包含了4个模块，其中`Node`定义了搜索的节点，`void IDS(int startId,int endId,Graph &graph){}` 是我实现IDFS算法主体，`void print_result(Graph &graph,int endId){}`用于根据搜索的结果打印一条路径。`mian()`则是程序执行入口。

- [代码](https://1541453904.rth1.me/IDS.html)

### （4）一致性代价搜索UCS

```cpp
#include "Graph.h"
#include "Timer.h"
#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node{};                          //一个节点结构，node

bool list[100];                         //用于记录是否走过
vector<node> frontier;                  //扩展节点集合
bool explored[100];                     //可访问集合
stack<int> road;                        //路径
int parent[100];                        //父节点

void UCS(int endCity,node &src,Graph &graph){}

void print_result(Graph &graph,int endId){}

int main(){}
```

- 程序说明

程序UCS.cpp主要包含了4个模块，其中`Node`定义了搜索的节点，`void UCS(int startId,int endId,Graph &graph){}` 是我实现UCS算法主体，`void print_result(Graph &graph,int endId){}`用于根据搜索的结果打印一条路径。`mian()`则是程序执行入口。

- [代码](https://1541453904.rth1.me/UCS.html)

### （5）贪婪最佳优先搜索GBFS

```cpp
#include "Graph.h"
#include "MyTime.h"
#include <stack>
#include <iostream>
#include <queue>
using namespace std;
struct Node{};                    //搜索节点

struct cmp{};                     //排序用到的结构

Node *root=NULL,*cur=NULL;           //创建树，用来保存IDS过程的节点信息
priority_queue<Node*,vector<Node*>,cmp>que;           
bool closeList[100];                 //可访问集合,true表示已经访问

void GBFS(int startId,int endId,Graph &graph){} //贪婪最佳优先

int cost=0;

void print_result(Graph &graph,Node * cur){}    //打印子节点
int main(){}
```

- 程序说明

程序GBFS.cpp主要包含了5个模块，其中`Node`定义了搜索的节点，`struct cmp{};`则是我排序用到的结构，`void GBFS(int startId,int endId,Graph &graph){}` 是我实现GBFS算法主体，`void print_result(Graph &graph,int endId){}`用于根据搜索的结果打印一条路径。`mian()`则是程序执行入口。

- [代码](https://1541453904.rth1.me/GBFS.html)

### （6）A*搜索AStart

```cpp
#include "Graph.h"
#include "MyTime.h"
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
struct node{};                           //一个节点结构，node

bool list[100];                          //用于记录是否走过
vector<node> openList;                   //扩展节点集合
bool closeList[100];                     //可访问集合
stack<int> road;                         //路径
int parent[100];                         //父节点
void A_star(int endId,node &src,Graph &graph){}

void print_result(Graph &graph,int endId){}

int main(){}
```

- 程序说明

程序`UCS.cpp`主要包含了4个模块，其中`node`定义了搜索的节点，`void A_star(int endId,node &src,Graph &graph){}` 是我实现A*算法主体，`void print_result(Graph &graph,int endId){}`用于根据搜索的结果打印一条路径。`mian()`则是程序执行入口。

- [代码](https://1541453904.rth1.me/AStar.html)

## 四、其他

### `Graph.h`：图类，用于记录图的信息

- [代码](https://1541453904.rth1.me/Graph.html)

### `Timer.h`：时间测试类，用于对运行程序进行时间测试

- [代码](https://1541453904.rth1.me/Timer.html)

### `graphInfo.txt`：图信息输入文本

- [文本](https://1541453904.rth1.me/graphInfo.html)
