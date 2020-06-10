#include <iostream>


void test1()
{   // 引用无法类型转换
    // double dval = 3.14;
    // int &rd = dval;
    // std::cout<<rd<<std::endl;

    // 但是常量引用可以
    double dval2 = 3.14;
    const int &rd2 = dval2;
    std::cout<<rd2<<std::endl;
}
int tr = 89;
int main(int argc, char **argv)
{
    static int a=0;
    constexpr int *pa = &a;
    
    

    return 0;
}