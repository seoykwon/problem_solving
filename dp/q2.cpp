#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int bridge[151];
int n;
int ans = INT_MIN;

int jump(int idx, int sum)
{
    if (idx > n)
    {
        ans = max(ans, sum);
        return ans;
    }

    // two steps
    sum += bridge[idx + 2];
    jump(idx + 2, sum);
    sum -= bridge[idx + 2];

    // 7 steps
    sum += bridge[idx + 7];
    jump(idx + 7, sum);
    sum -= bridge[idx + 7];
}

int main()
{
    // freopen("input.txt", "r", stdin);

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> bridge[i];
    }

    jump(0, 0);

    cout << ans;
}

// ################# 최적화 필요 dp 로 변환하기 ##################

#include <iostream>
#include <memory.h>
using namespace std;

int N, arr[200], dp[200];

int query(int n)
{
    if (n > N)
        return 0;
    if (dp[n] > -1e9)
        return dp[n]; // -10억보다 크면 이미 저장된 값이므로, 바로 사용한다.
    // 그렇지 않다면 계산한 값을 쓴다.
    int step2 = query(n + 2);
    int step7 = query(n + 7);
    // 계산한 값을 사용하고 리턴한다.
    dp[n] = max(step2, step7) + arr[n];
    return dp[n];
}

int main()
{
    memset(dp, 128, sizeof(dp)); // dp 테이블을 bit 단위로 초기화한다. 128을 넣으면 -10억보다 조금 더 작은 값이 할당된다.
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> arr[i];
    cout << query(0);
}

// ####################### 강사님 코드 Top Down ###############################
#include <iostream>
using namespace std;

int memo[1000];
int map[1000];

int getPoint(int n)
{
    if (n == 0)
        return 0;
    if (n < 0)
        return -999999;
    if (memo[n] != 0)
        return memo[n];

    int a = getPoint(n - 2);
    int b = getPoint(n - 7);

    int ret = a;
    if (ret < b)
        ret = b;

    memo[n] = ret + map[n];
    return memo[n];
}

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> map[i];

    int max = -21e8;
    //(n + 1) ~ (n + 5)
    for (int i = 1; i <= 5; i++)
    {
        int ret = getPoint(n + i);
        if (ret > max)
            max = ret;
    }

    cout << max;

    return 0;
}

// ############### Bottom Up ##########################
#include <iostream>
using namespace std;

int arr[200];
int dp[200];

int main()
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> arr[i];

    // Bottom-Up
    int MIN = -21e8;
    for (int i = 0; i <= N + 5; i++)
        dp[i] = MIN;

    // 일단 2칸씩 가는 칸을 모두 채움 -> 2에서 7칸을 점프해서 N을 5만큼 넘어갈수 있는 공간까지 확인한다
    dp[0] = 0;
    for (int i = 2; i <= N + 5; i++)
    {
        dp[i] = dp[i - 2] + arr[i];
    }

    // 7까지 점프하는 방법은 0->7 하나
    dp[7] = 7;
    // 이후로부터 특정 칸에 도달하기 위한 값 = 2칸 전에서 점프했거나, 7칸 전에서 점프했거나
    for (int i = 7; i <= N + 5; i++)
    {
        dp[i] = max(dp[i - 7] + arr[i], dp[i - 2] + arr[i]);
    }

    int ans = -21e8;

    // N~N+5까지의 공간중 최대값을 확인
    for (int i = N; i <= N + 5; i++)
    {
        if (dp[i] > ans)
            ans = dp[i];
    }
    cout << ans;
}