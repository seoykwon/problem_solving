#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
// i번째 물건까지 고려했을 떼, 부피가 j인 배낭에 담을 수 있는 최대 가치치
int dp[101][1001];
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
            // 각 물건의 부피와 가치
            cin >> w[i] >> v[i];
        }

        for (int i = 1; i <= N; i++)
        {
            for (int j = 0; j <= K; j++)
            {
                // 물건을 담지 않은 경우
                dp[i][j] = dp[i - 1][j];

                // 물건을 담은 경우우
                if (w[i] <= j && dp[i][j] < dp[i - 1][j - w[i]] + v[i])
                {
                    // 배낭의 용량 j가 물건의 부피보다 크거나 같으면 담기기
                    dp[i][j] = dp[i - 1][j - w[i]] + v[i];
                }
            }
        }

        cout << "#" << testcase << " " << dp[N][K] << endl;
    }

    return 0;
}
