#include <iostream>
using namespace std;
#define max(a, b) (a > b) ? a : b

int N;
int arr[1001];
int dp[1001];

int main(void)
{
    cin >> N;

    for (int i = 0; i < N; i++)
        cin >> arr[i];

    for (int i = 0; i < N; i++)
    {
        dp[i] = arr[i];
        for (int j = 0; j < i; j++)
        {
            // 증가하는 수열일 때, 합을 갱신한다.
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + arr[i]);
        }
    }

    int ans = dp[0];
    for (int i = 1; i < N; i++)
        if (ans < dp[i])
            ans = dp[i];

    cout << ans;

    return 0;
}
