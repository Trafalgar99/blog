# 题解：KMP字符串	

[AcWing 831. KMP字符串匹配](https://www.acwing.com/solution/content/7977/)

**题目描述**
给定一个模式串S，以及一个模板串P，所有字符串中只包含大小写英文字母以及阿拉伯数字。

模板串P在模式串S中多次作为子串出现。

求出模板串P在模式串S中所有出现的位置的起始下标。

**输入格式**
第一行输入整数N，表示字符串P的长度。

第二行输入字符串P。

第三行输入整数M，表示字符串S的长度。

第四行输入字符串S。

**输出格式**
共一行，输出所有出现位置的起始下标（下标从0开始计数），整数之间用空格隔开。

**数据范围**
1≤N≤1041≤N≤104
1≤M≤1051≤M≤105
**输入样例**：

3
aba
5
ababa
**输出样例**：

0 2



**解题思路：**

​		kmp字符串匹配算法，详见注释



`代码：`

```cpp
#include<iostream>

using namespace std;

const int N = 100010;

int m,n;
int p[N],s[N];

int ne[N];

int main()
{
    cin>>n>>p+1>>m>>s+1;
    //求next数组
    for(int i = 2,j=0;i<=n;i++)
    {
        while(j&&p[i]!=p[j+1]) j=ne[j];
        if(p[i]==p[j+1]) j++;
        ne[i] =j;
    }
    
    //匹配的过程
    for(int i=1,j=0;i<=m;i++)
    {
        while(j&&p[j+1]!=s[i]) j = ne[j];
        if(p[j+1] == s[i]) j++;
        if(j == n)
        {
            cout<<i-n<<endl;
            j = ne[j];
        }
    }

    return 0;
}
```



------

> Author: Trafal
>
> Editor: Typora
>
> Date: 2020.9.26