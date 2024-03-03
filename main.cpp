// #include "vector/vector.h"

#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    /*
    Vector<int> a;
    Vector<int> b;
    Vector<int> c;

    c.PushBack(123);
    c.PushBack(456);

    b.PushBack(123);
    b.PushBack(456);

    a.PushBack(1200);
    a.PushBack(123123123);

    a.Append(b);
    a += b;

    a = a + b;

    for (int i = 0; i < a.Size(); i++)
    {
        std::cout << a[i] << std::endl;
    }

    cout << endl;

    for (int i = 0; i < b.Size(); i++)
    {
        std::cout << b[i] << std::endl;
    }

    cout << (c != a) << endl;
    */

    string s = "aaaaa";

    string s;
    s.resize(1000);
    if (GetVolumePathNameA("E:\\Code\\Github\\WinDrv-Cpp-Libs", s.data(), 1000))
    {
        cout << s << endl;
        s.resize(strlen(s.data()));
        if (s[s.size()-1] == '\\')
        {
            s.pop_back();
        }
        string ans;
        ans.resize(1000);
        if (QueryDosDeviceA(s.data(), ans.data(), ans.size()) != 0)
        {
            cout << ans << endl;
        }
    }
    
}