/**
 * 2024-11-14 solved
 */

// #include <iostream>
// #include <string>
// #include <queue>

// using namespace std;

// struct node
// {
//     string str;
//     int cur;
// };

// string bfs(int start, int target)
// {
//     queue<node> q;
//     q.push({"", start});

//     while (!q.empty())
//     {
//         node now = q.front();
//         q.pop();

//         if (now.cur == target)
//         {
//             return now.str;
//         }

//         int next;
//         // Double
//         next = now.cur * 2;
//         if (next > 9999)
//         {
//             next = next % 10000;
//         }
//         q.push({now.str + 'D', next});

//         // Subtract
//         if (now.cur == 0)
//         {
//             next = 9999;
//         }
//         else
//         {
//             next = now.cur - 1;
//         }
//         q.push({now.str + 'S', next});

//         // Left rotate
//         int quotient = now.cur / 1000;
//         int remainder = now.cur % 1000;

//         string tmp = to_string(remainder) + to_string(quotient);
//         next = stoi(tmp);
//         q.push({now.str + 'L', next});

//         // Right rotate
//         quotient = now.cur / 10;
//         remainder = now.cur % 10;

//         tmp = to_string(remainder) + to_string(quotient);
//         next = stoi(tmp);
//         q.push({now.str + 'R', next});
//     }
// }

// int main()
// {
//     // freopen("input.txt", "r", stdin);

//     int N;
//     cin >> N;

//     for (int i = 0; i < N; i++)
//     {
//         int A, B;

//         cin >> A >> B;

//         string ans = bfs(A, B);

//         cout << ans << '\n';
//     }
// }

/**
 * visited 배열로 중복 처리 해 주지 않으면 시간 초과가 뜸
 * 아마도 left rotate, right rotate 구현을 위에서 틀린 것 같음.
 * 그래서 답이 온전히 다 똑같게 나오지 않음
 */

#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

// 동작을 정의한 함수들
// Double
int D(int x)
{
    return (x * 2) % 10000;
}

// Subtract
int S(int x)
{
    return (x == 0) ? 9999 : x - 1;
}

// Left rotate
int L(int x)
{
    return (x % 1000) * 10 + (x / 1000);
}

// Right rotate
int R(int x)
{
    return (x % 10) * 1000 + (x / 10);
}

// BFS 함수
string bfs(int start, int target)
{
    queue<pair<int, string>> q;
    vector<bool> visited(10000, false);
    q.push({start, ""});
    visited[start] = true;

    while (!q.empty())
    {
        int cur = q.front().first;
        string moves = q.front().second;
        q.pop();

        // 목표에 도달했으면 결과 반환
        if (cur == target)
        {
            return moves;
        }

        // 가능한 동작들
        // 1. Double
        int next = D(cur);
        if (!visited[next])
        {
            visited[next] = true;
            q.push({next, moves + "D"});
        }

        // 2. Subtract
        next = S(cur);
        if (!visited[next])
        {
            visited[next] = true;
            q.push({next, moves + "S"});
        }

        // 3. Left Rotate
        next = L(cur);
        if (!visited[next])
        {
            visited[next] = true;
            q.push({next, moves + "L"});
        }

        // 4. Right Rotate
        next = R(cur);
        if (!visited[next])
        {
            visited[next] = true;
            q.push({next, moves + "R"});
        }
    }

    return ""; // 도달할 수 없는 경우 (실제 입력에서는 발생하지 않음)
}

int main()
{
    // freopen("input.txt", "r", stdin);

    int N;
    cin >> N;

    while (N--)
    {
        int A, B;
        cin >> A >> B;

        // BFS를 사용하여 최소 동작 구하기
        string result = bfs(A, B);
        cout << result << endl;
    }

    return 0;
}
