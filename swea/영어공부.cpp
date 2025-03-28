#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, p;
vector<int> a;

int solve()
{
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int L = i, R = n - 1, mid;

        while (L <= R)
        {
            mid = (L + R) / 2;
            int blank = (a[mid] - a[i] + 1) - (mid - i + 1);
            if (blank > p)
            {
                R = mid - 1;
            }
            else
            {
                L = mid + 1;
                ans = max(ans, (a[mid] - a[i] + 1) + (p - blank));
            }
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int maximum_date = 1000001;
    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++)
    {
        cin >> n;
        cin >> p;

        a.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        int ans = solve();
        cout << "#" << test_case << " " << ans << "\n";
    }
}