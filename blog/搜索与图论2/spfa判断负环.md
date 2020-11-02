# spfa判断负环

**题目描述**
给定一个n个点m条边的有向图，图中可能存在重边和自环， 边权可能为负数。

请你判断图中是否存在负权回路。

**输入格式**
第一行包含整数n和m。

接下来m行每行包含三个整数x，y，z，表示点x和点y之间存在一条有向边，边长为z。

输出格式
如果图中存在负权回路，则输出“Yes”，否则输出“No”。

**数据范围**
1≤n≤2000
1≤m≤10000
图中涉及边长绝对值均不超过10000。

**输入样例**：
3 3
1 2 -1
2 3 4
3 1 -4
**输出样例**：
Yes

**解题思路**

spfa算法可以判断图中是否存在负环，维护一个当前节点最短路径上的边的数量的数组cnt，每次更新最短距离的时候同时更新cnt，紧接着判断当前cnt是否已经大于总边数，如果大于，则说明已经出现了负环。

**解题代码**

```cpp
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 150010;

int n,m;
int h[N],e[N],ne[N],w[N],idx;
int dist[N],cnt[N];
bool st[N];

void add(int a,int b,int c)
{
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}
bool spfa()
{
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    queue<int> q;//队列存储路径变短的点
    //为了找到初始点到达不了的负环，需要一开始就把所有点都放到队列里
    for(int i=1;i<=n;i++)
    {
        q.push(i);
        st[i] = true;
    }

    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;
        
        for(int i=h[t];i!=-1;i=ne[i])//尝试用路径已经变短的点去更新它的临边
        {
            int j=e[i];
            if(dist[j]>dist[t]+w[i])
            {
                dist[j] = dist[t]+w[i];
                cnt[j] = cnt[t]+1;//更新最短路的边数
                
                if(cnt[j]>=n) return true;//如果最短上的边数已经大于n了，则一定有负环
                
                if(!st[j])
                {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
    return false;
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
    if(spfa()) puts("Yes");
    else puts("No");
    
    return 0;
}
```

------

>  author: Trafal
>
> editor: Typora
>
> date: 11.02

