#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int arr[301] = {0}; // 계단 점수 저장
    int dp[301] = {0};  // DP 테이블

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // 초기값 설정
    dp[0] = arr[0];
    dp[1] = arr[0] + arr[1];
    dp[2] = max(arr[0] + arr[2], arr[1] + arr[2]);

    // DP 계산
    for (int i = 3; i < n; i++)
    {
        dp[i] = max(dp[i - 2] + arr[i], dp[i - 3] + arr[i - 1] + arr[i]);
    }

    // 결과 출력
    cout << dp[n - 1] << '\n';

    return 0;
}
