#include <iostream>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    while (n--)
    {
        string gauge;
        cin >> gauge;

        int sz = gauge.size();

        int idx;

        if (gauge[sz - 1] == '#')
        {
            cout << "100%" << '\n';
            continue;
        }

        for (int i = 0; i < sz; i++)
        {
            if (gauge[i] == '_')
            {
                idx = i;
                break;
            }
        }
        // casting needed
        cout << (double)idx / sz * 100 << '%' << '\n';
    }
}

// ########## the right code with binary and parametric search ####################
#include <iostream>
#include <string>
using namespace std;

void psearch(string s)
{
    int left = 0;
    int right = s.length() - 1;
    int ans = -1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (s[mid] == '#')
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout << (ans + 1) * 100 / s.length() << "%" << '\n';
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string s;
        cin >> s;
        psearch(s);
    }
}