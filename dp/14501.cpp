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

// #############################################
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> consult(n);
    for (int i = 0; i < n; i++)
    {
        cin >> consult[i].first >> consult[i].second; // Ti, Pi
    }

    vector<int> dp(n + 1, 0); // 퇴사일 이후까지 포함하여 0으로 초기화

    for (int i = n - 1; i >= 0; i--)
    {
        int Ti = consult[i].first;  // 상담에 필요한 기간
        int Pi = consult[i].second; // 상담을 했을 때 받는 금액

        dp[i] = dp[i + 1]; // 상담을 하지 않는 경우

        // 상담을 하는 경우
        if (i + Ti <= n)
        {
            dp[i] = max(dp[i], Pi + dp[i + Ti]);
        }
    }

    cout << dp[0] << endl;
    return 0;
}
