#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    int ans = INT_MAX;

    vector<int> packages;
    vector<int> indiv;

    while (m--)
    {
        int package, each;
        cin >> package >> each;

        packages.push_back(package);
        indiv.push_back(each);
    }

    sort(packages.begin(), packages.end());
    sort(indiv.begin(), indiv.end());

    int quotient = n / 6;
    int remainder = n % 6;

    // case 1: buying only packages
    if (remainder)
    {
        ans = min(ans, (quotient + 1) * packages[0]);
    }
    else
    {
        ans = min(ans, quotient * packages[0]);
    }

    // case 2: buy packages + each
    ans = min(ans, (quotient * packages[0] + remainder * indiv[0]));

    // case 3: buy only each
    ans = min(ans, n * indiv[0]);

    cout << ans << '\n';
    return 0;
}