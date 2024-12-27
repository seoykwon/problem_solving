#include <iostream>
using namespace std;

int n;
int res = 0;

void go(int num)
{
    if (num == n)
    {
        res += 1;
    }
    if (num > n)
    {
        return;
    }
    go(num + 1);
    go(num + 2);
    go(num + 3);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int t;
    cin >> t;

    while (t--)
    {
        cin >> n;
        res = 0;

        go(0);

        cout << res << '\n';
    }
}

// ##########################
#include <iostream>
using namespace std;

int main()
{
    int t, n;
    cin >> t; // 테스트 케이스 수

    while (t--)
    {
        cin >> n;
        int dp[11] = {0}; // 최대 n의 범위가 11 이하라고 가정
        dp[0] = 1;        // 초기값

        for (int i = 1; i <= n; i++)
        {
            if (i >= 1)
                dp[i] += dp[i - 1];
            if (i >= 2)
                dp[i] += dp[i - 2];
            if (i >= 3)
                dp[i] += dp[i - 3];
        }

        cout << dp[n] << '\n'; // n을 나타내는 방법의 수 출력
    }

    return 0;
}