#include <iostream>

using namespace std;
typedef long long ll;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    ll dp[1000001];

    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 15746;
    }

    cout << dp[n] << '\n';
    return 0;
}