#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> things(n); // 물건의 무게와 가치
    for (int i = 0; i < n; i++)
    {
        cin >> things[i].first >> things[i].second;
    }

    // DP 배열 초기화 (1차원 배열 사용)
    vector<int> dp(k + 1, 0);

    for (int i = 0; i < n; i++)
    {
        int w = things[i].first;  // 현재 물건의 무게
        int v = things[i].second; // 현재 물건의 가치

        // 뒤에서 앞으로 갱신
        for (int j = k; j >= w; j--)
        {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }

    cout << dp[k] << endl; // 최대 가치 출력
    return 0;
}
