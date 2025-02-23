#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        int ans = 0;

        int n, m;
        cin >> n >> m;

        unordered_set<string> first;

        for (int i = 0; i < n; i++)
        {
            string str;
            cin >> str;
            first.insert(str);
        }

        for (int i = 0; i < m; i++)
        {
            string str;
            cin >> str;
            if (first.count(str) > 0)
            {
                ans++;
            }
        }

        cout << "#" << t << " " << ans << '\n';
    }
    return 0;
}