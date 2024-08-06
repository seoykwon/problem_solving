// #include <iostream>
// #include <queue>
// #include <vector>
// #include <algorithm>

// using namespace std;

// vector<pair<int, int>> v[100001];
// int visited[100001];
// int cost[100001] = {
//     0,
// };
// int cnt = 0;
// vector<pair<int, int>> path;
// int n, m, k;

// void input()
// {
//     cin >> n >> m >> k;

//     for (int i = 0; i < m; i++)
//     {
//         int a, b, c;

//         cin >> a >> b >> c;

//         v[a].push_back(make_pair(b, c));
//     }
// }

// void bfs(int start)
// {
//     queue<int> q;
//     // visited[start] = 1;
//     q.push(start);
//     cost[start] = 0;

//     while (!q.empty())
//     {
//         int next = q.front();
//         q.pop();

//         for (int i = 0; i < v[next].size(); i++)
//         {
//             if (!visited[v[next][i].first])
//             {
//                 q.push(v[next][i].first);
//                 visited[v[next][i].first] = 1;
//                 cost[v[next][i].first] += v[next][i].second + cost[next];
//                 path.push_back(make_pair(v[next][i].first, cost[v[next][i].first]));
//             }
//         }
//     }

//     for (int i = 0; i < path.size(); i++)
//     {
//         if (cost[i] <= k && cost[i] > 0)
//         {
//             cnt++;
//         }
//     }
// }

// int main()
// {
//     input();

//     bfs(1);

//     cout << cnt;
// }

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    int num;
    long long cost;
};

vector<Node> v[100001];
int n, m, k;
long long dist[100001];

void bfs(int node)
{
    queue<Node> q;
    q.push({node, 0});

    dist[node] = 0;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < v[now.num].size(); i++)
        {
            Node next = v[now.num][i];
            dist[next.num] = dist[now.num] + next.cost;
            q.push({next.num, next.cost});
        }
    }

    int cnt = 0;
    for (int i = 2; i <= n; i++)
    {
        if (dist[i] > 0 && dist[i] <= k)
            cnt++;
    }
    cout << cnt;
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        v[from].push_back({to, cost});
    }
    bfs(1);
}