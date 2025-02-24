#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
int dp[101][1001];
int w[101], v[101];
int ans;

int main() {
    int T;
    cin >> T;

    for (int testcase = 1; testcase <= T; testcase++) {
        cin >> N >> K;
        for (int i = 1; i <= N; i++) {
            cin >> w[i] >> v[i];
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= K; j++) {
                dp[i][j] = dp[i - 1][j];

                if (w[i] <= j && dp[i][j] < dp[i - 1][j - w[i]] + v[i]) {
                    dp[i][j] = dp[i - 1][j - w[i]] + v[i];
                }
            }
        }

        cout << "#" << testcase << " " << dp[N][K] << endl;
    }

    return 0;
}
