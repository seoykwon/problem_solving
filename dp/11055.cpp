#include <iostream>
#include <algorithm>

using namespace std;

int n;
int arr[1001];
int dp[1001];

int main()
{
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // DP 배열 초기화
    for (int i = 0; i < n; i++)
    {
        dp[i] = arr[i];
    }

    int ans = 0;

    // LIS 계산
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                dp[i] = max(dp[i], dp[j] + arr[i]);
                // dp[i] = max(dp[i], dp[j] + dp[i]); 는 틀림
            }
        }
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';

    return 0;
}
