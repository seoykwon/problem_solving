#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);

    int tc; // 테스트 케이스 수
    cin >> tc;

    while (tc--)
    {
        int n;
        cin >> n;

        int sticker[2][100001] = {0}; // 스티커 점수
        int dp[2][100001] = {0};      // DP 테이블

        // 스티커 입력 받기
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> sticker[i][j];
            }
        }

        // 초기 상태 설정
        dp[0][0] = sticker[0][0];
        dp[1][0] = sticker[1][0];

        if (n > 1)
        {
            dp[0][1] = sticker[1][0] + sticker[0][1];
            dp[1][1] = sticker[0][0] + sticker[1][1];
        }

        // DP 테이블 채우기
        for (int i = 2; i < n; i++)
        {
            dp[0][i] = max(dp[1][i - 1], dp[1][i - 2]) + sticker[0][i];
            dp[1][i] = max(dp[0][i - 1], dp[0][i - 2]) + sticker[1][i];
        }

        // 두 행의 마지막 열 중 최댓값이 정답
        cout << max(dp[0][n - 1], dp[1][n - 1]) << '\n';
    }

    return 0;
}
