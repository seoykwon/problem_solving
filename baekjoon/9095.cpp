#include <iostream>

using namespace std;

int n;
int nums[11];
int cnt;

void find(int target, int cur)
{
    if (cur == target)
    {
        cnt++;
        return;
    }
    if (cur > target)
    {
        return;
    }

    find(target, cur + 1);
    find(target, cur + 2);
    find(target, cur + 3);
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    for (int i = 0; i < n; i++)
    {
        find(nums[i], 0);
        cout << cnt << '\n';
    }

    return 0;
}

// ############# 중복 제거 ####################
#include <iostream>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    int t, n;
    cin >> t; // 테스트 케이스 수

    while (t--)
    {
        cin >> n;
        int dp[11] = {0}; // 최대 n의 범위가 11 이하라고 가정
        dp[0] = 1;        // 초기값

        for (int i = 1; i <= n; i++)
        {
            if (i >= 1)
                dp[i] += dp[i - 1];
            if (i >= 2)
                dp[i] += dp[i - 2];
            if (i >= 3)
                dp[i] += dp[i - 3];
        }

        cout << dp[n] << '\n'; // n을 나타내는 방법의 수 출력
    }

    return 0;
}
