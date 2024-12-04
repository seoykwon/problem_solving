#include <iostream>
#include <algorithm>

using namespace std;

int n;
int arr[1001];
int dp[1001];

int main()
{
    // freopen("input.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // DP 배열 초기화
    fill(dp, dp + n, 1); // 각 요소에서의 최대 길이는 최소 1

    int ans = 1;

    // LIS 계산
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';

    return 0;
}
