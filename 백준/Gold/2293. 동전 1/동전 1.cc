#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n, k;
    cin >> n >> k;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    vector<int> dp(k + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++)
    { // 각 동전에 대해
        // if (coins[i] > k)
        //     continue;

        // dp[coins[i]]++; // i원 코인 하나로 i원 어치를 만들 수 있음

        for (int j = coins[i]; j <= k; j++)
        { // 해당 동전의 가치부터 k까지
            dp[j] += dp[j - coins[i]];
        }
    }

    cout << dp[k] << '\n'; // 가치의 합이 k가 되는 경우의 수 출력
    return 0;
}
