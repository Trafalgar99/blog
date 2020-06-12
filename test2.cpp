#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iterator>
#include <cstddef>

using namespace std;
void test1()
{ // 引用无法类型转换
    // double dval = 3.14;
    // int &rd = dval;
    // std::cout<<rd<<std::endl;

    // 但是常量引用可以
    double dval2 = 3.14;
    const int &rd2 = dval2;
    std::cout << rd2 << std::endl;
}
int tr = 89;

int main(int argc, char **argv)
{
    // string s1{"sdfs"};
    // string &s2 = s1;
    // getline(cin, s1);
    // for (decltype(s1.size()) index = 0; index != s1.size() && !isspace(s1[index]); ++index)
    // {
    //     s1[index] = toupper(s1[index]);
    // }

    // vector<string> v2{8};
    // vector<int>::const_iterator vv = v2.end();
    // auto v = v2.begin();
    // auto mid = v2.begin() + v2.size() / 2;
    // v++;
    // int arr[] = {
    //     1,
    //     3,
    //     2,
    //     2,
    // };
    // auto a = begin(arr), b = end(arr);
    // auto c = b - a;

    // string s;
    // auto aa = s.c_str();

    // int iaa[][2] = {
    //     {1, 2},
    //     {3, 4}};
    // for (auto &row : iaa)
    //     for (auto col : row)
    //         cout << col;

    // int arr[3] = {1, 2, 3};
    // auto a = arr;
    // int(&sa)[3] = arr;
    // int (*re)[3] = arr;

    return 0;
}