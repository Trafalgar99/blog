# 题解：Dijkstra求最短路

**题目描述**

给定一个n个点m条边的有向图，图中可能存在重边和自环，所有边权均为正值。

请你求出1号点到n号点的最短距离，如果无法从1号点走到n号点，则输出-1。

**输入格式**

第一行包含整数n和m。

接下来m行每行包含三个整数x，y，z，表示存在一条从点x到点y的有向边，边长为z。

**输出格式**

输出一个整数，表示1号点到n号点的最短距离。

如果路径不存在，则输出-1。

**数据范围**

1≤n≤500
1≤m≤10^5
图中涉及边长均不超过10000。

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

使用朴素Dijkstra算法即可，算法思路为，从初始点开始，依次遍历所有的点，每次都把距离当前节点距离为1的节点的距离更新，并且标记这些点的状态为已经更新，再找到这些点中距离父节点的距离最近的点，将其作为下一个迭代的对象，用他去更新所有与他距离为一的点，知道找到最后一个节点。

**解题代码**

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 510;

int n,m;
int g[N][N]; //用邻接表存储边的信息
int dist[N];
bool st[N];

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist); //初始化距离
    dist[1] = 0;
    for(int i=0;i<n;i++)
    {
        int t = -1;
        for(int j=1;j<=n;j++) //在所有st[i]==false的点里找到dist[i]最小的点
            if(!st[N]&&(t==-1||dist[t]>dist[j]))
                t = j;
        
        if(t == n)break;
        
        st[t] = true; //将这个点标记为已确定最短路径的点
        
        for(int j=1;j<=n;j++) //用这个点更新所有点
            dist[j] == min(dist[j], dist[t]+g[t][j]);
    }
    
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}
int main()
{
    memset(g, 0x3f, sizeof g);
    cin>>n>>m;
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        g[a][b] = min(g[a][b],c); //题目中可能存在重边，只取最短的边
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

