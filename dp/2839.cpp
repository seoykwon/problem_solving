#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int result = -1; // 결과를 초기화 (-1은 실패의 의미)

    // 5킬로그램 봉지를 최대한 사용하며, 남은 설탕을 3킬로그램 봉지로 나눌 수 있는지 확인
    for (int i = n / 5; i >= 0; i--)
    {
        int remaining = n - (i * 5); // 5킬로그램 봉지로 처리한 후 남은 설탕
        if (remaining % 3 == 0)
        {                                 // 남은 설탕이 3으로 나누어 떨어지는 경우
            result = i + (remaining / 3); // 봉지의 총 개수
            break;                        // 가장 적은 봉지로 해결되므로 루프 종료
        }
    }

    cout << result << '\n'; // 결과 출력
    return 0;
}

// ########################
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    // DP 배열 초기화
    vector<int> dp(n + 1, 5000); // 큰 값으로 초기화
    dp[0] = 0;                   // 0kg은 봉지 0개로 가능

    // DP 점화식 계산
    for (int i = 3; i <= n; i++)
    {
        if (i >= 3)
            dp[i] = min(dp[i], dp[i - 3] + 1);
        if (i >= 5)
            dp[i] = min(dp[i], dp[i - 5] + 1);
    }

    // 결과 출력
    if (dp[n] == 5000)
    {
        cout << -1 << '\n'; // 정확히 만들 수 없는 경우
    }
    else
    {
        cout << dp[n] << '\n'; // 최소 봉지 개수 출력
    }

    return 0;
}
