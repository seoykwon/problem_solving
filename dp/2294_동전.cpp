// 2025-08-31 
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int dp[10001] = {0,};
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> money(n + 1);
    for (int i = 1; i <= n; i++) cin >> money[i];

    for (int i = 1; i <= k; i++) dp[i] = 10001;

    for (int i = 1; i <= n; i++) {
        for (int j = money[i]; j <= k; j++){
            dp[j] = min(dp[j], dp[j - money[i]] + 1);
        }
    }

    if (dp[k] == 10001) cout << -1 << '\n';
    else cout << dp[k] << '\n';
}