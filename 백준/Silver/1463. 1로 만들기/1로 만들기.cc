#include <iostream>
#include <algorithm> // std::min 사용

using namespace std;

int main()
{
    int n;
    cin >> n;

    int dp[1000001]; // N은 1 ≤ N ≤ 1,000,000

    dp[1] = 0; // 1은 이미 1이므로 연산 필요 없음

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + 1; // 기본적으로 1을 빼는 연산

        if (i % 2 == 0)
        {
            dp[i] = min(dp[i], dp[i / 2] + 1); // 2로 나누는 연산
        }
        if (i % 3 == 0)
        {
            dp[i] = min(dp[i], dp[i / 3] + 1); // 3으로 나누는 연산
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
