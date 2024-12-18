#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    int cards[1001] = {
        0,
    };
    for (int i = 1; i <= n; i++)
    {
        cin >> cards[i];
    }

    int dp[1001] = {
        0,
    };
    // int mx = 0;

    // for (int i = n; i > 0; i--)
    // {
    //     int next = n - ((n / i) * i);

    //     dp[i] = cards[i] * (n / i) + cards[next];
    //     mx = max(mx, dp[i]);
    // }

    // 위 방식은 현재 i 인덱스 값을 최대한으로 가져가는 경우의 수만 있음

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            dp[i] = max(dp[i], dp[i - j] + cards[j]);
        }
    }

    // cout << mx << '\n';
    cout << dp[n] << '\n';
    return 0;
}