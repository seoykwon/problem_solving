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

// ############## Top down ########################
#include <iostream>
using namespace std;

int memo[10000];
int dong[10000];
int dn;

int getMinCnt(int t)
{
    if (t == 0)
    {
        return 0;
    }
    if (t < 0)
        return 21e8;
    if (memo[t] != 0)
        return memo[t];

    int min = 21e8;
    for (int i = 0; i < dn; i++)
    {
        int ret = getMinCnt(t - dong[i]);
        if (ret < min)
            min = ret;
    }

    memo[t] = min + 1;
    return min + 1;
}

int main()
{
    // freopen("text.txt", "r", stdin);

    int t, n;
    cin >> t >> dn;
    for (int i = 0; i < dn; i++)
        cin >> dong[i];

    int ret = getMinCnt(t);

    if (ret >= 21e8)
    {
        cout << "impossible";
        return 0;
    }

    cout << ret;
    return 0;
}

// ################## Bottom Up ######################
#include <iostream>
using namespace std;

// index : 특정 거스름돈 액수
// value : 그 거스름돈을 돌려주기 위한 최소 동전 개수
int dp[3001];
int target; // 만들어야 하는 거스름돈
int N;
int coins[100];

int main()
{
    cin >> target >> N;
    for (int i = 0; i < N; i++)
        cin >> coins[i];
    // cout << func(target);

    // Bottom-Up
    // #0. 최소값
    for (int i = 0; i <= target; i++)
        dp[i] = 21e8;
    // #1. 찾을 수 있는 가장 작은 문제에 대한 해답
    dp[0] = 0;

    // 모든 코인에 대해서 테이블을 채운다
    for (int i = 0; i < N; i++)
    {
        int now = coins[i];
        for (int j = now; j <= target; j++)
        {
            if (dp[j - now] + 1 < dp[j])
                dp[j] = dp[j - now] + 1;
        }
    }
    if (dp[target] >= 21e8)
        cout << "impossible";
    else
        cout << dp[target];
}