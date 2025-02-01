// #include <iostream>
// #include <queue>
// #include <cstring>
// using namespace std;
// typedef pair<int, int> pii;

// int complete[10] = {
//     0,
// };

// bool check(int checkNum)
// {
//     while (checkNum)
//     {
//         int idx = checkNum % 10;

//         checkNum /= 10;

//         complete[idx] = 1;
//     }

//     for (int i = 0; i < 10; i++)
//     {
//         if (complete[i] == 0)
//         {
//             return false;
//         }
//     }
//     return true;
// }

// int bfs(int num)
// {
//     queue<pii> q;
//     q.push(make_pair(num, 1));

//     while (!q.empty())
//     {
//         int curNum = q.front().first;
//         int order = q.front().second;
//         q.pop();

//         if (check(curNum))
//         {
//             return order;
//         }

//         // q.push(make_pair((order + 1) * curNum, order + 1));
//         q.push(make_pair((order + 1) * num, order + 1));
//     }
// }

// int main()
// {
//     freopen("input.txt", "r", stdin);
//     int t;
//     cin >> t;

//     for (int i = 1; i <= t; i++)
//     {
//         memset(complete, 0, sizeof(complete));
//         int n;
//         cin >> n;
//         int ans = 0;

//         ans = bfs(n);

//         cout << "#" << i << " " << ans << '\n';
//     }
// }

// /**
//  * 문제점 및 개선 사항
// 전역 배열 complete 사용 문제

// complete 배열이 전역 변수로 선언되어 있어 여러 테스트 케이스에서 초기화되지 않을 수 있습니다.
// 해결: complete을 전역이 아닌 함수 내부에서 관리하도록 변경.
// BFS 탐색 구조 비효율성

// bfs() 함수에서 q.push(make_pair((order + 1) * curNum, order + 1));를 사용하고 있는데, 여기서 (order + 1) * curNum이 아니라 (order + 1) * num이 되어야 올바른 계산이 됩니다.
// 해결: curNum이 아니라 num을 기준으로 곱셈을 수행.
// 불필요한 queue 사용

// BFS를 사용할 필요가 없음. 단순히 반복문을 통해 kN을 체크하는 방식이 더 효율적.
// 해결: 불필요한 BFS 제거하고 단순 반복문 사용.
//  */

#include <iostream>
#include <cstring>
using namespace std;

int find_min_count(int n)
{
    bool seen[10] = {false}; // 0~9까지 본 숫자를 체크하는 배열
    int count = 0;
    int num = 0;

    while (true)
    {
        count++;
        num = count * n;

        // 현재 숫자의 각 자릿수를 체크
        int temp = num;
        while (temp > 0)
        {
            seen[temp % 10] = true;
            temp /= 10;
        }

        // 모든 숫자를 봤다면 종료
        bool all_seen = true;
        for (int i = 0; i < 10; i++)
        {
            if (!seen[i])
            {
                all_seen = false;
                break;
            }
        }
        if (all_seen)
            return count;
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++)
    {
        int n;
        cin >> n;
        int ans = find_min_count(n);
        cout << "#" << i << " " << ans * n << '\n';
    }

    return 0;
}
