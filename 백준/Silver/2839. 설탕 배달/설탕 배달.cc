#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    // DP 배열 초기화
    vector<int> dp(n + 1, 5000); // 큰 값으로 초기화
    dp[0] = 0; // 0kg은 봉지 0개로 가능

    // DP 점화식 계산
    for (int i = 3; i <= n; i++) {
        if (i >= 3) dp[i] = min(dp[i], dp[i - 3] + 1);
        if (i >= 5) dp[i] = min(dp[i], dp[i - 5] + 1);
    }

    // 결과 출력
    if (dp[n] == 5000) {
        cout << -1 << '\n'; // 정확히 만들 수 없는 경우
    } else {
        cout << dp[n] << '\n'; // 최소 봉지 개수 출력
    }

    return 0;
}
