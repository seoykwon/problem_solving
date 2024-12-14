#include <iostream>
typedef long long ll;

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    ll dp[91];

    dp[1] = 1;
    dp[2] = 1;

    for (int i = 3; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << dp[n];

    return 0;
}
