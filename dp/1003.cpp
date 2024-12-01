#include <iostream>

using namespace std;

int cnt0 = 0;
int cnt1 = 1;

int fibonacci(int n)
{
    if (n == 0)
    {
        // printf("0");
        cnt0++;
        return 0;
    }
    else if (n == 1)
    {
        // printf("1");
        cnt1++;
        return 1;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int t;
    cin >> t;

    while (t--)
    {
        int num;
        cin >> num;

        cnt0 = 0;
        cnt1 = 0;

        fibonacci(num);

        cout << cnt0 << " " << cnt1 << '\n';
    }
    return 0;
}

// ######## 시간 초과 ######################3
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