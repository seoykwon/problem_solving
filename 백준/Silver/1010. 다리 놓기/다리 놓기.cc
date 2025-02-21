#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int T; // 테스트 케이스 수
    cin >> T;

    while (T--)
    {
        int N, M; // 서쪽과 동쪽의 사이트 수
        cin >> N >> M;

        // DP 테이블 초기화
        vector<vector<int>> dp(M + 1, vector<int>(N + 1, 0));

        // DP를 이용해 조합 계산
        for (int i = 0; i <= M; i++)
        {
            for (int j = 0; j <= min(i, N); j++)
            {
                if (j == 0 || j == i)
                {
                    dp[i][j] = 1; // C(M, 0) = 1 또는 C(M, M) = 1
                }
                else
                {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                }
            }
        }

        // 결과 출력
        cout << dp[M][N] << endl;
    }

    return 0;
}
// 조합을 사용해 푸는 문제가 아님
// 조합의 정의를 사용함
/**
 * C(M, N) = C(M - 1, N - 1) + C(M - 1, N)
 * C(M - 1, N - 1): M번째 요소를 선택한 경우
 * C(M - 1, N): M번째 요소를 선택하지 않은 경우
 *
 * 초기값
 * C(M, 0) = 1 (0개를 선택하는 경우는 항상 1가지)
 * C(M, M) = 1 (M개 중 M개를 모두 선택하는 경우는 1가지)
 *
 *
 */