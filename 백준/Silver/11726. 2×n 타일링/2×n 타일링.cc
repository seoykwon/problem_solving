#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // DP 배열 선언
    int dp[1001];

    // 초기값 설정
    dp[1] = 1; // 2×1 크기의 직사각형을 채우는 방법: 1가지
    dp[2] = 2; // 2×2 크기의 직사각형을 채우는 방법: 2가지

    // DP 점화식 계산
    for (int i = 3; i <= n; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;
    }

    // 결과 출력
    cout << dp[n] << endl;

    return 0;
}
