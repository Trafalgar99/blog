# 题解：第k个数

> [第k个数](https://www.acwing.com/problem/content/788/)

给定一个长度为n的整数数列，以及一个整数k，请用快速选择算法求出数列的第k小的数是多少。

#### 输入格式

第一行包含两个整数 n 和 k。

第二行包含 n 个整数（所有整数均在1~109109范围内），表示整数数列。

#### 输出格式

输出一个整数，表示数列的第k小数。

#### 数据范围

1≤n≤1000001≤n≤100000,
1≤k≤n

#### 输入样例：

```
5 3
2 4 1 5 3
```

#### 输出样例：

```
3
```

这道题可以用`快速排序`的思路来解决，如果选定第一个l元素作为基准，快速排序的每次循环会将这个元素排好，通过检查循环变量，我们可以知道这个被排好的元素是第j-l+1个数，如果`j-l+1 > k`，则代表我们要找的数还在这个基准前面；反之，则代表我们要在这个被排好的基准元素后面找(k-i-1)小的数

cpp：

```cpp
#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int n, k;
int q[N];

int find_k_min(int q[], int l, int r, int k)
{
    if (l >= r)
        return q[l];
    int x = q[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j)
    {
        do
            i++;
        while (q[i] < x);
        do
            j--;
        while (q[j] > x);
        if (i < j)
            swap(q[i], q[j]);
    }
    int s = j - l + 1; //该元素是第s小的数
    if (s >= k)
        find_k_min(q, l, j , k);
    else
        find_k_min(q, j + 1, r, k - s);
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);
    cout << find_k_min(q, 0, n - 1, k);

    return 0;
}
```

