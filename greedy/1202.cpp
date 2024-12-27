// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// bool cmp(pair<int, int> a, pair<int, int> b)
// {
//     if (a.second > b.second)
//         return true;
//     if (a.second < b.second)
//         return false;
//     return false;
// }

// int main()
// {
//     freopen("input.txt", "r", stdin);
//     int n, k;
//     cin >> n >> k;

//     vector<pair<int, int>> gem;
//     vector<int> bag;
//     for (int i = 0; i < n; i++)
//     {
//         int a, b;
//         cin >> a >> b;
//         gem.push_back({a, b});
//     }
//     for (int i = 0; i < k; i++)
//     {
//         int tmp;
//         cin >> tmp;
//         bag.push_back(tmp);
//     }

//     sort(bag.begin(), bag.end());
//     sort(gem.begin(), gem.end(), cmp);

//     int sum = 0;

//     for (int i = 0; i < bag.size(); i++)
//     {
//         for (int j = 0; j < gem.size(); j++)
//         {
//             if (gem[j].first <= bag[i])
//             {
//                 sum += gem[j].second;
//                 gem.erase(gem.begin() + j);
//                 break;
//             }
//         }
//     }

//     cout << sum << '\n';
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> gem(n);
    vector<int> bag(k);

    for (int i = 0; i < n; i++)
    {
        cin >> gem[i].first >> gem[i].second; // {무게, 가격}
    }
    for (int i = 0; i < k; i++)
    {
        cin >> bag[i]; // 가방 용량
    }

    // 보석과 가방 정렬
    sort(gem.begin(), gem.end()); // 무게 기준 오름차순
    sort(bag.begin(), bag.end()); // 용량 기준 오름차순

    priority_queue<int> pq;
    long long sum = 0;
    int index = 0;

    for (int i = 0; i < k; i++)
    {
        // 현재 가방에 넣을 수 있는 보석 모두 추가
        while (index < n && gem[index].first <= bag[i])
        {
            pq.push(gem[index].second); // 가격만 추가
            index++;
        }

        // 가장 비싼 보석을 선택
        if (!pq.empty())
        {
            sum += pq.top();
            pq.pop();
        }
    }

    cout << sum << '\n';
    return 0;
}
