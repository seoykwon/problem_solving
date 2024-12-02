#include <iostream>
using namespace std;

int main() {
    int tc;
    cin >> tc;

    while (tc--) {
        int k, n;
        cin >> k >> n;

        int dp[15][15] = {0};

        // 0층 초기화
        for (int i = 1; i <= n; i++) {
            dp[0][i] = i;
        }

        // DP 계산
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
            }
        }

        // 결과 출력
        cout << dp[k][n] << '\n';
    }

    return 0;
}
