#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    string s, t;
    cin >> s >> t;

    while (1)
    {
        if (t[t.size() - 1] == 'A')
        {
            t.pop_back();
        }
        else
        {
            t.pop_back();
            reverse(t.begin(), t.end());
        }
        if (t.size() == s.size())
        {
            if (t == s)
                cout << 1;
            else
                cout << 0;
            break;
        }
    }
    return 0;
}