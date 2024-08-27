// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// const int MAX_INDEX = 1500; // We need to compute up to the 1500th Ugly Number

// // Function to generate Ugly Numbers up to the MAX_INDEX
// vector<int> generateUglyNumbers(int max_count)
// {
//     vector<int> ugly_numbers(max_count);
//     vector<int> indexes(3, 0); // To keep track of indices for 2, 3, and 5
//     vector<int> next_ugly(3);  // Next potential Ugly Numbers

//     // Initialize the first Ugly Number
//     ugly_numbers[0] = 1;
//     next_ugly[0] = 2;
//     next_ugly[1] = 3;
//     next_ugly[2] = 5;

//     for (int i = 1; i < max_count; ++i)
//     {
//         // Find the smallest among the next possible ugly numbers
//         int next = min(min(next_ugly[0], next_ugly[1]), next_ugly[2]);
//         ugly_numbers[i] = next;

//         // Update the next possible ugly numbers
//         if (next == next_ugly[0])
//         {
//             indexes[0]++;
//             next_ugly[0] = ugly_numbers[indexes[0]] * 2;
//         }
//         if (next == next_ugly[1])
//         {
//             indexes[1]++;
//             next_ugly[1] = ugly_numbers[indexes[1]] * 3;
//         }
//         if (next == next_ugly[2])
//         {
//             indexes[2]++;
//             next_ugly[2] = ugly_numbers[indexes[2]] * 5;
//         }
//     }

//     return ugly_numbers;
// }

// int main()
// {
//     // freopen("input.txt", "r", stdin);
//     int Q;
//     cin >> Q;

//     vector<int> queries(Q);
//     for (int i = 0; i < Q; ++i)
//     {
//         cin >> queries[i];
//     }

//     // Precompute Ugly Numbers up to the maximum index needed
//     vector<int> ugly_numbers = generateUglyNumbers(MAX_INDEX);

//     // Output the results for each query
//     for (int i = 0; i < Q; ++i)
//     {
//         int k = queries[i];
//         cout << ugly_numbers[k - 1] << " ";
//     }
//     cout << endl;

//     return 0;
// }

#include <iostream>
#include <queue>
#define ll long long
using namespace std;
priority_queue<ll, vector<ll>, greater<ll>> q;

ll result[1600];

int main()
{
    q.push(1);

    int cnt = 0;
    ll now = 0;
    ll old = -1;

    while (1)
    {
        now = q.top();
        q.pop();
        if (old == now)
            continue;
        old = now;

        cnt++;
        result[cnt] = now;
        if (cnt == 1500)
            break;

        q.push(now * 2);
        q.push(now * 3);
        q.push(now * 5);
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int tar;
        cin >> tar;
        cout << result[tar] << " ";
    }

    return 0;
}