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
// ################################################

#include <bits/stdc++.h>

using namespace std;

int n, sum, ans;
int coin[101];
int dp[10001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> sum;
    for (int i = 0; i < n; i++)
    {
        cin >> coin[i];
    }

    for (int i = 0; i < n; i++)
    {
        if (coin[i] > sum)
        {
            continue;
        }
        dp[coin[i]]++; // i원 코인 하나로 무조건 i원 어치를 만들 수 있으므로 1추가
        for (int j = coin[i]; j <= sum; j++)
        {
            dp[j] = dp[j] + dp[j - coin[i]];
        }
    }
    cout << dp[sum];
}

/* https://velog.io/@hgo641/%EB%B0%B1%EC%A4%80-2293-%EB%8F%99%EC%A0%841-C-%ED%92%80%EC%9D%B4
 */