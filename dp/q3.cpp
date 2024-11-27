#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

string minCoins(int T, int n, vector<int> &coins)
{
    const int INF = 1e9;        // 무한 값 설정
    vector<int> dp(T + 1, INF); // dp 배열 초기화
    dp[0] = 0;                  // 0원을 만드는 데는 동전 0개 필요

    // 각 동전으로 dp 배열 갱신
    for (int coin : coins)
    {
        for (int i = coin; i <= T; ++i)
        {
            if (dp[i - coin] != INF)
            {                                         // i - coin 금액을 만들 수 있으면
                dp[i] = min(dp[i], dp[i - coin] + 1); // 최소 동전 수 갱신
            }
        }
    }

    // T원을 만들 수 없으면 "impossible" 반환
    if (dp[T] == INF)
    {
        return "impossible";
    }

    // 최소 동전 수 반환
    return to_string(dp[T]);
}

int main()
{
    freopen("input.txt", "r", stdin);
    int T, n;
    cin >> T >> n; // 물품의 가치와 동전의 개수 입력
    vector<int> coins(n);

    // 동전의 가치 입력
    for (int i = 0; i < n; ++i)
    {
        cin >> coins[i];
    }

    // 결과 출력
    cout << minCoins(T, n, coins) << endl;

    return 0;
}
