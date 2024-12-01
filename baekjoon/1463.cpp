#include <iostream>
#include <algorithm> // std::min 사용
#include <climits>   // INT_MAX 사용

using namespace std;

int n;
int minOperations = INT_MAX; // 최소 연산 횟수를 저장

void dfs(int current, int operations)
{
    // 종료 조건: 현재 값이 1이 된 경우
    if (current == 1)
    {
        minOperations = min(minOperations, operations);
        return;
    }

    // 백트래킹: 현재 연산 횟수가 최소값보다 크면 탐색 중단
    if (operations >= minOperations)
    {
        return;
    }

    // 3으로 나누어 떨어지면 3으로 나누는 경우 탐색
    if (current % 3 == 0)
    {
        dfs(current / 3, operations + 1);
    }

    // 2로 나누어 떨어지면 2로 나누는 경우 탐색
    if (current % 2 == 0)
    {
        dfs(current / 2, operations + 1);
    }

    // 1을 빼는 경우 탐색
    dfs(current - 1, operations + 1);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n;

    dfs(n, 0); // 시작 숫자 n에서 연산 횟수 0으로 시작
    cout << minOperations << '\n';

    return 0;
}

// ####################### dp ##########################
#include <iostream>
#include <algorithm> // std::min 사용

using namespace std;

int main()
{
    int n;
    cin >> n;

    int dp[1000001]; // N은 1 ≤ N ≤ 1,000,000

    dp[1] = 0; // 1은 이미 1이므로 연산 필요 없음

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + 1; // 기본적으로 1을 빼는 연산

        if (i % 2 == 0)
        {
            dp[i] = min(dp[i], dp[i / 2] + 1); // 2로 나누는 연산
        }
        if (i % 3 == 0)
        {
            dp[i] = min(dp[i], dp[i / 3] + 1); // 3으로 나누는 연산
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
