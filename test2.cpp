#include <iostream>
#include <string>
#include <vector>
#include <cctype>
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
    string s1{"sdfs"};
    string &s2 = s1;
    getline(cin, s1);
    for (decltype(s1.size()) index = 0; index != s1.size() && !isspace(s1[index]); ++index)
    {
        s1[index] = toupper(s1[index]);
    }
    return 0;
}