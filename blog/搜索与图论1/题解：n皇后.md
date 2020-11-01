# 题解：n皇后

**问题描述**：n-皇后问题是指将 n 个皇后放在 n∗n 的国际象棋棋盘上，使得皇后不能相互攻击到，即任意两个皇后都不能处于同一行、同一列或同一斜线上。

![img](https://cdn.acwing.com/media/article/image/2019/06/08/19_860e00c489-1_597ec77c49-8-queens.png)

现在给定整数n，请你输出所有的满足条件的棋子摆法。

**输入格式**

共一行，包含整数n。

**输出格式**

每个解决方案占n行，每行输出一个长度为n的字符串，用来表示完整的棋盘状态。

其中”.”表示某一个位置的方格状态为空，”Q”表示某一个位置的方格上摆着皇后。

每个方案输出完成后，输出一个空行。

输出方案的顺序任意，只要不重复且没有遗漏即可。

**数据范围**

1≤n≤91≤n≤9

**输入样例：**

```
4
```

**输出样例：**

```
.Q..
...Q
Q...
..Q.

..Q.
Q...
...Q
.Q..
```

**解题思路：**

由题目描述可以知道，每行只有可能有一个皇后，故可以循环每一行，每次循环都检查每一行的每一列可不可以放置皇后，用深度优先搜索实现循环每一行。

**解题代码：**

```cpp
#include<iostream>

using namespace std;

const int N = 20;

int n;
char g[N][N]; //存储每一个结果
int col[N],deg[N],udeg[N]; //存储一个位置是否可以放置皇后的相关信息（列，对角线，反对角线）

void dfs(int x)
{
    if(x == n) //已经搜索完了最后一行，输出结果
    {
        for(int i=0;i<n;i++)
            puts(g[i]);
        cout<<endl;
        return;
    }
    for(int i=0;i<n;i++) //在一行中遍历每一个位置
    {
        if(!col[i]&&!deg[x+i]&&!udeg[n-x+i]) //符合皇后放置条件
        {
            g[x][i] = 'Q';
            col[i] = deg[x+i] = udeg[n-x+i] = true; //更新条件
            dfs(x+1);
            col[i] = deg[x+i] = udeg[n-x+i] = false; //回溯时要还原条件
            g[x][i] = '.';
        }
    }
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++) //初始化
        for(int j=0;j<n;j++)
            g[i][j] = '.';
    dfs(0);
    return 0;
}
```

------

> Author: Trafal
>
> Date: 2020.11.1
>
> Editor: Typora	

