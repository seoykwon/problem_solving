#include <iostream>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        int dp[41][2] = {
            0,
        };
        dp[0][0] = 1;
        dp[0][1] = 0;
        dp[1][0] = 0;
        dp[1][1] = 1;

        for (int i = 2; i <= n; i++)
        {
            dp[i][0] = dp[i - 1][0] + dp[i - 2][0];
            dp[i][1] = dp[i - 1][1] + dp[i - 2][1];
        }

        cout << dp[n][0] << " " << dp[n][1] << '\n';
    }
    return 0;
}