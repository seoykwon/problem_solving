#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int K;
// i번째 물건까지 고려했을 때, 부피가 j인 배낭에 담을 수 있는 최대 가치치
int dp[101][1001];
// 물건 i를 배낭에 담았는지 여부를 추적하는 배열.
// 1: 물건 i를 담지 않음. 2: 물건 i를 담음.
int come[101][1001];
// 물건의 부피, 가치
int w[101], v[101];
int ans;

int main()
{
    int T;
    cin >> T;

    for (int testcase = 1; testcase <= T; testcase++)
    {
        cin >> N >> K;
        for (int i = 1; i <= N; i++)
        {
            cin >> w[i] >> v[i];
        }

        for (int i = 1; i <= N; i++)
        {
            for (int j = 0; j <= K; j++)
            {
                dp[i][j] = dp[i - 1][j];
                // 물건 i 담지 않음음
                come[i][j] = 1;

                if (w[i] <= j)
                {
                    if (dp[i][j] < dp[i - 1][j - w[i]] + v[i])
                    {
                        dp[i][j] = dp[i - 1][j - w[i]] + v[i];
                        // 물건 i 담음음
                        come[i][j] = 2;
                    }
                }
            }
        }

        vector<int> used(N + 1, 0); // used[i] := i번 물건이 사용되었는가?
        int j = K;                  // 현재 가방 용량

        for (int i = N; i >= 1; i--)
        {
            if (come[i][j] == 1)
            {
                used[i] = 0;
            }
            else
            {
                used[i] = 1;
                j -= w[i];
            }
        }

        for (int i = 1; i <= N; i++)
        {
            cout << i << "번 물건 사용: " << used[i] << endl;
        }

        cout << "#" << testcase << " " << dp[N][K] << endl;
    }

    return 0;
}
