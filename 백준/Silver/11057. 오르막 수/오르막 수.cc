#include <iostream>
using namespace std;

int dp[1001][10]; // dp[i][j]: 길이가 i이고, 마지막 숫자가 j인 오르막 수의 개수

int main()
{
    int n;
    cin >> n;

    // 초기화: 길이가 1인 경우 각 자리수에 대해 1로 초기화
    for (int j = 0; j <= 9; j++) {
        dp[1][j] = 1;
    }

    // DP 점화식 계산
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 9; j++) {
            if (j == 0) {
                dp[i][j] = dp[i - 1][j]; // 0으로 끝나는 경우는 이전 길이의 0으로 끝나는 경우와 동일
            } else {
                dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % 10007; // 점화식
            }
        }
    }

    // 결과 계산: 길이가 N인 모든 오르막 수의 합
    int ans = 0;
    for (int j = 0; j <= 9; j++) {
        ans = (ans + dp[n][j]) % 10007;
    }

    cout << ans << '\n';
    return 0;
}
