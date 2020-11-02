# spfa求最短路

**题目描述**

给定一个n个点m条边的有向图，图中可能存在重边和自环， **边权可能为负数**。

请你求出1号点到n号点的最短距离，如果无法从1号点走到n号点，则输出impossible。

数据保证不存在负权回路。

**输入格式**

第一行包含整数n和m。

接下来m行每行包含三个整数x，y，z，表示存在一条从点x到点y的有向边，边长为z。

**输出格式**

输出一个整数，表示1号点到n号点的最短距离。

如果路径不存在，则输出”impossible”。

**数据范围**

1≤n,m≤10^5
图中涉及边长绝对值均不超过10000。

**输入样例：**

```
3 3
1 2 5
2 3 -3
1 3 4
```

**输出样例：**

```
2
```

**解题思路**

spfa算法是堆Bellman-Ford算法的一个改良版，Bellman-Ford算法的缺点在于只是单纯首尾循环了每一条边，而没有考虑到每次循环是否有效，只有用距离变小了的点取更新其他的点的距离，其他点的距离才有可能变小，spfa算法就是在这里做了优化，用一个栈保存所有距离变小了的节点，用这些点去更新其余点，使得每次更新都是有效的。

**解题代码**

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

const int N = 1500010;

int n,m;
int h[N],e[N],ne[N],w[N],idx; //用邻接表存储边
int dist[N];
bool st[N]; //表示当前点是否已经在队列中

void add(int a, int b, int c)
{
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}
int spfa()
{
    memset(dist,0x3f,sizeof dist); //初始化
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    st[1] = true;
    
    while(q.size())
    {
        int t == q.front();
        q.pop();
        st[t] = false;
        
        for(int i=h[t];i!=-1;i=ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i]) //更新其他点
            {
                dist[j] = dist[t] + w[i];
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}
int main()
{
    memset(h,-1,sizeof h);
    cin>>n>>m;
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
    }
    int t = spfa();
    if(t == -1)
        puts("-1");
    else cout<<t<<endl;
}
```

------

>  author: Trafal
>
> editor: Typora
>
> date: 11.02

