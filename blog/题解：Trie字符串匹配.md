# 题n解：Trie字符串匹配



**题目描述**
维护一个字符串集合，支持两种操作：

“I x”向集合中插入一个字符串x；
“Q x”询问一个字符串在集合中出现了多少次。
共有N个操作，输入的字符串总长度不超过 105，字符串仅包含小写英文字母。

**输入格式**
第一行包含整数N，表示操作数。

接下来N行，每行包含一个操作指令，指令为”I x”或”Q x”中的一种。

**输出格式**
对于每个询问指令”Q x”，都要输出一个整数作为结果，表示x在集合中出现的次数。

每个结果占一行。

**数据范围**
1≤N≤2∗104

**样例**
**输入样例**：
5
I abc
Q abc
Q ab
I ab
Q ab
**输出样例**：
1
0
1



**解题思路：**

这道题应该使用Trie结构存储数据

1、插入过程
对于一个单词，从根开始，沿着单词的各个字母所对应的树中的节点分支向下走，直到单词遍历完，将最后的节点标记为红色，表示该单词已插入Trie树。
2、查询过程
同样的，从根开始按照单词的字母顺序向下遍历trie树，一旦发现某个节点标记不存在或者单词遍历完成而最后的节点未标记为红色，则表示该单词不存在，若最后的节点标记为红色，表示该单词存在。



`代码`

```cpp
#include<iostream>

using namespace std;

const int N = 100010;

int son[N][26],cnt[N],idx;
char str[N];

void insert(char str[])
{
    int p = 0; //代表第一个节点，也代表当前节点
    for(int i=0;str[i];i++)	//插入过程
    {
        int u = str[i]-'a'; // 字母映射为数字
        if(son[p][u]==0) son[p][u] = ++idx;	//如果还没有这个节点，就新建这个节点
        p=son[p][u];	//更新当前节点
    }
    cnt[p]++;	//当前单词的数量加一
}

int query(char str[])
{
    int p = 0;
    for(int i=0; str[i]; i++)
    {
        int u = str[i]-'a';
        if(son[p][u] == 0) return 0;
        p = son[p][u];
    }
    return cnt[p];
}


int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        char op[2];
        cin>>op>>str;
        if(op[0]=='I')
        {
            insert(str);
        }
        else
        {
            cout<<query(str)<<endl;
        }
    }
    
    return 0;
}
```





------

> Author: Trafal
>
> Date: 2020.10.2
>
> Editor: Typora