#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++)
    {
        long long N;
        cin >> N;

        long long L = 1;
        long long R = 10000000000LL;
        long long res = 0;

        while (L <= R)
        {
            long long mid = (L + R) / 2;
            long long value = mid * (mid + 1) / 2;

            if (N >= value)
            {
                res = mid;
                L = mid + 1;
            }
            else
            {
                R = mid - 1;
            }
        }

        long long value = res * (res + 1) / 2;
        if (N != value)
        {
            res = -1;
        }
        cout << "#" << test_case << " " << res << "\n";
    }
    return 0;
}