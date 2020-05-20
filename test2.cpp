#include <cctype>
#include <iostream>
#include <string>
#include<vector>

using namespace std;

int main(void)
{
    vector<vector<int>> v;
    string s("Hello world!!");
    for (auto &c: s)
        c = toupper(c);

    cout<<s<<endl;
}