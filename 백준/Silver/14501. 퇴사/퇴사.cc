#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    vector<pair<int, int>> consult;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;

        consult.push_back({a, b});
    }

    int dp[16] = {
        0,
    };

    for (int i = n - 1; i >= 0; i--)
    {
        // 상담 안 함
        dp[i] = dp[i + 1];

        // 상담 함
        if (i + consult[i].first <= n)
        {
            dp[i] = max(dp[i], dp[i + consult[i].first] + consult[i].second);
        }
    }

    cout << dp[0] << '\n';
    return 0;
}