#include <iostream>
#include <algorithm> // max 함수를 사용하기 위해 포함
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n; // 포도주 잔의 개수
    cin >> n;

    int wine[10001]; // 각 잔에 들어있는 포도주의 양을 저장
    int dp[10001];   // i번째 잔까지 고려했을 때 최대 포도주의 양을 저장

    // 포도주 양 입력받기
    for (int i = 1; i <= n; ++i)
    {
        cin >> wine[i];
    }

    // 초기 조건 설정
    dp[1] = wine[1]; // 첫 번째 잔만 마시는 경우
    if (n > 1)
    {
        dp[2] = wine[1] + wine[2]; // 첫 번째 잔과 두 번째 잔을 모두 마시는 경우
    }

    // 동적 계획법으로 최대 포도주 양 계산
    for (int i = 3; i <= n; ++i)
    {
        // i번째 잔까지 고려했을 때의 최대 포도주 양 계산
        dp[i] = max({
            dp[i - 1],                        // i번째 잔을 마시지 않는 경우
            dp[i - 2] + wine[i],              // i번째 잔을 마시고, i-1번째 잔은 마시지 않는 경우
            dp[i - 3] + wine[i - 1] + wine[i] // i번째 잔과 i-1번째 잔을 마시고, i-2번째 잔은 마시지 않는 경우
        });
    }

    // 결과 출력: n번째 잔까지 고려했을 때의 최대 포도주의 양
    cout << dp[n] << endl;

    return 0;
}
