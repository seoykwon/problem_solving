#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int T; // Number of test cases
    cin >> T;

    vector<int> testCases(T);
    int maxN = 0; // To find the largest N among the test cases

    for (int i = 0; i < T; i++)
    {
        cin >> testCases[i];
        maxN = max(maxN, testCases[i]);
    }

    // Dynamic programming array to store Padovan sequence
    vector<long long> dp(maxN + 1, 0);

    // Base cases
    dp[1] = dp[2] = dp[3] = 1;

    // Fill the DP array using the recurrence relation
    for (int i = 4; i <= maxN; i++)
    {
        dp[i] = dp[i - 2] + dp[i - 3];
    }

    // Output results for each test case
    for (int i = 0; i < T; i++)
    {
        cout << dp[testCases[i]] << endl;
    }

    return 0;
}
