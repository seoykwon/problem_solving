#include <iostream>
#include <vector>
#include <algorithm> // max 함수 사용
using namespace std;

int main()
{
    int n;
    cin >> n; // 삼각형의 크기 입력

    // 삼각형 데이터를 저장할 2차원 벡터
    vector<vector<int>> triangle(n, vector<int>(n, 0));
    vector<vector<int>> dp(n, vector<int>(n, 0)); // DP 테이블

    // 삼각형 값 입력받기
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            cin >> triangle[i][j];
        }
    }

    // DP 테이블 초기화: 삼각형의 마지막 층을 그대로 복사
    for (int j = 0; j < n; ++j)
    {
        dp[n - 1][j] = triangle[n - 1][j];
    }

    // 아래층부터 위층으로 DP 테이블 갱신
    for (int i = n - 2; i >= 0; --i)
    { // n-2층부터 최상단까지
        for (int j = 0; j <= i; ++j)
        {
            // 현재 위치 값 + 아래층에서 선택 가능한 두 값 중 최대값
            dp[i][j] = triangle[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
        }
    }

    // 최상단의 값이 최대 합
    cout << dp[0][0] << endl;

    return 0;
}
