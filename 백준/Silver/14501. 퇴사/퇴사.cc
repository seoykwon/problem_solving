#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    // 상담 정보 저장
    vector<pair<int, int>> consult(n);
    for (int i = 0; i < n; i++) {
        cin >> consult[i].first >> consult[i].second; // Ti, Pi
    }

    // dp 배열 초기화
    vector<int> dp(n + 1, 0); // 퇴사일 이후까지 포함하여 0으로 초기화

    // 상담을 거꾸로 탐색하면서 최대 수익 계산
    for (int i = n - 1; i >= 0; i--) {
        int Ti = consult[i].first;  // 상담에 필요한 기간 (항상 1)
        int Pi = consult[i].second; // 상담을 했을 때 받는 금액

        // 상담을 하지 않는 경우
        dp[i] = dp[i + 1];

        // 상담을 하는 경우
        if (i + Ti <= n) {
            dp[i] = max(dp[i], Pi + dp[i + Ti]);
        }
    }

    // 첫 번째 날부터 시작해서 얻을 수 있는 최대 수익 출력
    cout << dp[0] << endl;

    return 0;
}
