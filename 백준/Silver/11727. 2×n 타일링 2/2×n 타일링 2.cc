#include <iostream>
using namespace std;

const int MOD = 10007;

int main()
{
    int n;
    cin >> n;

    // DP array to store the number of ways to tile a 2×i rectangle
    int dp[1001];

    // Base cases
    dp[1] = 1; // Only one way to tile a 2×1 rectangle
    dp[2] = 3; // Three ways to tile a 2×2 rectangle: (vertical, two horizontal, one 2×2)

    // Fill the DP array for 2×n rectangles
    for (int i = 3; i <= n; i++)
    {
        dp[i] = (dp[i - 1] + 2 * dp[i - 2]) % MOD;
    }

    // Output the result for 2×n rectangle
    cout << dp[n] << endl;

    return 0;
}
