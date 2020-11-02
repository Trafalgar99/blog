# 题解：Dijkstra求最短路（堆优化版本）

**题目描述**

 给定一个n个点m条边的有向图，图中可能存在重边和自环，所有边权均为非负值。

请你求出1号点到n号点的最短距离，如果无法从1号点走到n号点，则输出-1。

**输入格式**

第一行包含整数n和m。

接下来m行每行包含三个整数x，y，z，表示存在一条从点x到点y的有向边，边长为z。

**输出格式**

输出一个整数，表示1号点到n号点的最短距离。

如果路径不存在，则输出-1。

**数据范围**

1≤n,m≤1.5×10^5
图中涉及边长均不小于0，且不超过10000。

**输入样例：**

```
3 3
1 2 2
2 3 1
1 3 4
```

**输出样例：**

```
3
```

**解题思路**

在朴素Dijkstra算法中，有一步操作是找到路径最小的点，可以用堆进行优化。

**解题代码**

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

typedef pair<int,int> PII;

const int N = 150010;

int n,m;
int h[N],e[N],ne[N],w[N],idx; //用邻接表存储边的信息
int dist[N];
int st[N];

void add(int a,int b,int c)
{
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}

int dijkstra()
{
    memset(dist,0x3f,sizeof dist); //初始化距离
    dist[1] = 0;
    
    priority_queue<PII,vector<PII>,greater<PII>> heap; //用堆存储节点信息
    heap.push({0,1}); // first：距离 second：节点编号
    
    while(heap.size())
    {
        auto t = heap.top(); //t为距离父节点最短的的点
        heap.pop();
        
        int ver = t.second,d = t.first; //取出各个信息
        if(ver == n) break;
        if(st[ver]) continue;
        st[ver] = true;
        
        for(int i=h[ver];i!=-1;i=ne[i]) //用这个点更新所有点
        {
            int j = e[i];
            if(dist[j] > d+w[i])
            {
                dist[j] = d + w[i];
                heap.push({dist[j],j});
            }
        }
    }
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}
int main()
{
    memset(h,-1,sizeof h); //初始化邻接表头
    cin>>n>>m;
    
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
    }
    
    cout<<dijkstra()<<endl;
}
```

------

> author: Trafal
>
> editor: Typora
>
> date: 11.02