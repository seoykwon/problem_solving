#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int num;
        cin >> num;

        int dp[num + 1][2] = {0};
        // dp[i][0]: f(0) 호출 횟수, dp[i][1]: f(1) 호출 횟수

        // 초기 조건 설정
        dp[0][0] = 1; // f(0) 호출 시 f(0) = 1번 호출
        dp[0][1] = 0; // f(0) 호출 시 f(1) = 0번 호출
        dp[1][0] = 0; // f(1) 호출 시 f(0) = 0번 호출
        dp[1][1] = 1; // f(1) 호출 시 f(1) = 1번 호출

        for (int i = 2; i <= num; i++)
        {
            dp[i][0] = dp[i - 1][0] + dp[i - 2][0];
            dp[i][1] = dp[i - 1][1] + dp[i - 2][1];
        }

        cout << dp[num][0] << " " << dp[num][1] << '\n';
    }
    return 0;
}