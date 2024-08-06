// #include <iostream>
// #include <queue>
// #include <vector>
// #include <algorithm>

// using namespace std;

// struct pairs
// {
//     int dest;
//     int cost;
// };

// int visited[11];
// vector<pairs> v[11];
// vector<pairs> path;
// int n, m, k;
// int price[11] = {
//     0,
// };

// void input()
// {
//     cin >> n >> m >> k;

//     for (int i = 0; i < m; i++)
//     {
//         int a, b, c;

//         cin >> a >> b >> c;
//         pairs tmp = {b, c};
//         v[a].push_back(tmp);
//     }
// }

// bool cmp(pairs a, pairs b)
// {
//     return a.dest < b.dest;
// }

// void bfs(int node)
// {
//     queue<int> q;
//     visited[node] = 1;
//     q.push(node);

//     while (!q.empty())
//     {
//         int next = q.front();
//         q.pop();

//         for (int i = 0; i < v[next].size(); i++)
//         {
//             if (!visited[v[next][i].dest])
//             {
//                 q.push(v[next][i].dest);
//                 visited[v[next][i].dest] = 1;
//                 int dest_idx = v[next][i].dest;
//                 price[dest_idx] += v[next][i].cost + price[next];

//                 path.push_back({v[next][i].dest, price[dest_idx]});
//             }
//         }
//     }

//     sort(path.begin(), path.end(), cmp);

//     for (int i = 0; i < path.size(); i++)
//     {
//         if (path[i].cost <= k)
//         {
//             cout << path[i].dest << " ";
//         }
//     }
// }

// int main()
// {
//     input();

//     bfs(0);
// }

// code optimization using pair

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int visited[11];
vector<pair<int, int>> v[11];
vector<pair<int, int>> path;
int n, m, k;
int price[11] = {
    0,
};

void input()
{
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;

        cin >> a >> b >> c;

        v[a].push_back(make_pair(b, c));
    }
}

// bool cmp(pair a, pair b)
// {
//     return a.dest < b.dest;
// }

void bfs(int node)
{
    queue<int> q;
    visited[node] = 1;
    q.push(node);

    while (!q.empty())
    {
        int next = q.front();
        q.pop();

        for (int i = 0; i < v[next].size(); i++)
        {
            if (!visited[v[next][i].first])
            {
                q.push(v[next][i].first);
                visited[v[next][i].first] = 1;
                int dest_idx = v[next][i].first;
                price[dest_idx] += v[next][i].second + price[next];

                path.push_back({v[next][i].first, price[dest_idx]});
            }
        }
    }

    sort(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
    {
        if (path[i].second <= k)
        {
            cout << path[i].first << " ";
        }
    }
}

int main()
{
    input();

    bfs(0);
}