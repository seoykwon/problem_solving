#include <iostream>
#include <cstring>
using namespace std;

int T;
int N;
int list[101];
int diff[101];
int target = 0;
int sum = 0;

int water()
{
    for (int i = 0; i < N; i++)
    {
        if (target == list[i])
            continue;

        diff[i] = target - list[i];

        sum += diff[i];
    }

    if (sum == 0)
    {
        return 0;
    }

    int res = sum / 2;
    int rem = sum % 2;

    int two, one;
    two = res;
    one = rem;

    while (1)
    {
        if (abs(two - one) == 1)
        {
            break;
        }
        two--;
        one += 2;
    }

    return (one + two + 1);
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        memset(list, 0, sizeof(list));
        memset(diff, 0, sizeof(diff));
        cin >> N;
        target = 0;
        sum = 0;

        for (int i = 0; i < N; i++)
        {
            cin >> list[i];

            target = max(target, list[i]);
        }

        int ans = water();

        cout << "#" << tc << " " << ans << endl;
        // cout << "# target" << " " << target << endl;
    }
}