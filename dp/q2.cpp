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
