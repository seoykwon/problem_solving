// #include <iostream>
// #include <cstring>
// using namespace std;

// int T;
// int N;
// int list[101];
// int diff[101];
// int target = 0;
// int sum = 0;

// int water()
// {
//     for (int i = 0; i < N; i++)
//     {
//         if (target == list[i])
//             continue;

//         diff[i] = target - list[i];

//         sum += diff[i];
//     }

//     if (sum == 0)
//     {
//         return 0;
//     }

//     int res = sum / 2;
//     int rem = sum % 2;

//     int two, one;
//     two = res;
//     one = rem;

//     while (1)
//     {
//         if (abs(two - one) == 1 || abs(two - one) == 0)
//         {
//             break;
//         }
//         two--;
//         one += 2;
//     }

//     if (abs(two - one) == 0)
//     {
//         return one + two;
//     }
//     if (one == 1 && two == 0)
//     {
//         return 1;
//     }
//     return (one + two + 1);
// }

// int main()
// {
//     // freopen("input.txt", "r", stdin);

//     cin >> T;

//     for (int tc = 1; tc <= T; tc++)
//     {
//         memset(list, 0, sizeof(list));
//         memset(diff, 0, sizeof(diff));
//         cin >> N;
//         target = 0;
//         sum = 0;

//         for (int i = 0; i < N; i++)
//         {
//             cin >> list[i];

//             target = max(target, list[i]);
//         }

//         int ans = water();

//         cout << "#" << tc << " " << ans << endl;
//         // cout << "# target" << " " << target << endl;
//     }
// }

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    int noTest;
    cin >> noTest;

    for (int test = 0; test < noTest; test++)
    {
        int noTree, maxHeight = 0;
        cin >> noTree;

        vector<int> farm(noTree, 0);
        for (auto &value : farm)
        {
            cin >> value;
            maxHeight = max(maxHeight, value);
        }

        int twoFactor = 0, oneFactor = 0;
        for (const auto &value : farm)
        {
            twoFactor += (maxHeight - value) / 2;
            oneFactor += (maxHeight - value) % 2;
        }

        while (twoFactor > 0)
        {
            const int nowGap = abs(twoFactor - oneFactor);
            const int nextGap = abs((twoFactor - 1) - (oneFactor + 2));

            if (nowGap < nextGap)
                break;
            twoFactor -= 1, oneFactor += 2;
        }

        int totalDay = 0;
        if (twoFactor > oneFactor)
            totalDay = twoFactor * 2;
        else if (twoFactor < oneFactor)
            totalDay = oneFactor * 2 - 1;
        else
            totalDay = twoFactor + oneFactor;

        cout << "#" << test + 1 << " " << totalDay << endl;
    }

    return 0;
}