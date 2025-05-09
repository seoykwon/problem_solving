#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string a;
    string b;
    string t = "";

    cin >> a >> b;
    int a_len = a.length();
    int b_len = b.length();

    for (int i = 0; i < a.length(); i++)
    {
        t += a[i];
        if (t.length() >= b_len)
        {
            bool flag = true;

            for (int j = 0; j < b_len; j++)
            {
                if (t[t.length() - b_len + j] != b[j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                t.erase(t.end() - b_len, t.end());
        }
    }
    if (t.empty())
        cout << "FRULA" << '\n';
    else
        cout << t << '\n';
    return 0;
}