#include <bits/stdc++.h>
using namespace std;

int res;

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> building(n);
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> building[i];
    }

    for (int i = 0; i < n; i++)
    {
        double max_level = INT_MIN;
        for (int j = i + 1; j < n; j++)
        {
            double level = (double)(building[j] - building[i]) / (j - i);

            if (level > max_level)
            {
                cnt[i]++;
                cnt[j]++;
                max_level = level;
            }
        }
    }

    for (auto elem : cnt)
        res = max(res, elem);
    cout << res << '\n';
    return 0;
}