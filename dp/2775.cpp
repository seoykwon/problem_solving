#include <iostream>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int tc;
    cin >> tc;

    while (tc--)
    {
        int k, n;
        cin >> k >> n;

        // 어레이 0으로 초기화 안 해주면 답 틀림.
        int dp[15][15] = {0};

        // 인원수 초기화 n까지 포함해 줘야 함
        for (int i = 1; i <= n; i++)
        {
            dp[0][i] = i;
        }

        // 중첩 계산을 하게 됨
        // for (int i = 1; i <= k; i++)
        // {
        //     for (int j = 1; j <= n; j++)
        //     {
        //         for (int f = 1; f <= j; f++)
        //         {
        //             dp[i][j] += dp[i - 1][f];
        //         }
        //     }
        // }

        // DP 계산
        for (int i = 1; i <= k; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
            }
        }

        cout << dp[k][n] << '\n';
    }
}