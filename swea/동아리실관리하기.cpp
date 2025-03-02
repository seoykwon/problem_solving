#include <iostream>
#include <vector>
#define MOD 1000000007

using namespace std;

int countWays(const string &responsible)
{
    int N = responsible.size();
    vector<vector<int>> dp(N, vector<int>(16, 0)); // dp[i][subset]: i일까지 subset 조합 경우의 수

    int firstDayLeader = responsible[0] - 'A';

    // 첫째 날 초기화 (A는 반드시 포함)
    for (int subset = 1; subset < 16; subset++)
    {
        if ((subset & (1 << firstDayLeader)) && (subset & 1))
        {
            dp[0][subset] = 1;
        }
    }

    // DP 테이블 채우기
    for (int i = 1; i < N; i++)
    {
        int leader = responsible[i] - 'A';

        for (int prev = 1; prev < 16; prev++)
        { // 전날 조합
            if (dp[i - 1][prev] == 0)
                continue;

            for (int next = 1; next < 16; next++)
            { // 오늘 조합
                if (!(next & (1 << leader)))
                    continue; // 책임자 포함 안 됨
                if (!(prev & next))
                    continue; // 전날과 오늘 교집합 없음

                dp[i][next] = (dp[i][next] + dp[i - 1][prev]) % MOD;
            }
        }
    }

    // 결과 계산
    int result = 0;
    for (int subset = 1; subset < 16; subset++)
    {
        result = (result + dp[N - 1][subset]) % MOD;
    }

    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        string responsible;
        cin >> responsible;
        cout << "#" << t << " " << countWays(responsible) << "\n";
    }

    return 0;
}
