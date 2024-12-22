#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // DP 배열 선언
    int dp[1001];

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;

    for (int i = 3; i <= n; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;
    }

    // 결과 출력
    cout << dp[n] << endl;

    return 0;
}
