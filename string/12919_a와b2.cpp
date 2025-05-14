// 시간 초과 남, 그리고 틀림림
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string S, T;

void input()
{
    cin >> S;
    cin >> T;
}

int solve()
{
    while (1)
    {
        if (T == S)
        {
            return 1;
        }
        if (T.length() == S.length())
        {
            break;
        }
        // add A to the end of String
        if (T[T.size() - 1] == 'A')
        {
            T.pop_back();
        }
        // add B to the end and reverse
        if (T[0] == 'B')
        {
            reverse(T.begin(), T.end());
            T.pop_back();
        }
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);

    input();

    int ans = solve();

    cout << ans << '\n';
}

// ########################
#include <iostream>
#include <algorithm>
using namespace std;

string S, T;
bool result;

void dfs(string now)
{
    if (result)
        return;
    if (S == now)
    {
        result = true;
        return;
    }
    if (S.size() >= T.size())
        return;

    string tmp = now;

    if (tmp[0] == 'B' && tmp.back() == 'B')
    {
        reverse(tmp.begin(), tmp.end());
        tmp.pop_back();
        dfs(tmp);
    }
    else if (tmp[0] == 'A' && tmp.back() == 'A')
    {
        tmp.pop_back();
        dfs(tmp);
    }
    else if (tmp[0] == 'B' && tmp.back() == 'A')
    {
        tmp.pop_back();
        dfs(tmp);

        tmp = now;
        reverse(tmp.begin(), tmp.end());
        tmp.pop_back();
        dfs(tmp);
    }
    else
        return;
}

void solution()
{
    dfs(T);

    cout << result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> S;
    cin >> T;

    solution();

    return 0;
}