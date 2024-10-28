// #include <iostream>
// #include <queue>
// #include <climits>

// using namespace std;

// int N, A, B;
// int field[31][31];
// int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
// int dist[31][31];

// // 1 = ground, 2 = water
// struct Edge
// {
//     int y, x, cost;

//     bool operator<(Edge right) const
//     {
//         if (cost < right.cost)
//             return false;
//         if (cost > right.cost)
//             return true;
//         return false;
//     }
// };

// int dijkstra(int sy, int sx, int dy, int dx)
// {
//     priority_queue<Edge> pq;
//     fill(&dist[0][0], &dist[0][0] + 31 * 31, INT_MAX);
//     dist[sy][sx] = 0;
//     pq.push({sy, sx, 0});

//     while (!pq.empty())
//     {
//         Edge now = pq.top();
//         pq.pop();

//         if (now.y == dy && now.x == dx)
//         {
//             return dist[dy][dx];
//         }

//         if (dist[now.y][now.x] < now.cost)
//             continue;

//         for (int i = 0; i < N; i++)
//         {
//             int ny = now.y + dir[i][0];
//             int nx = now.x + dir[i][1];

//             if (ny < 0 || nx < 0 || ny >= N || nx >= N)
//                 continue;

//             int nc;

//             if (field[now.y][now.x] == field[ny][nx])
//             {
//                 nc = A;
//             }
//             else
//             {
//                 nc = B;
//             }

//             int nextcost = dist[now.y][now.x] + nc;

//             if (dist[ny][nx] > nextcost)
//             {
//                 dist[ny][nx] = nextcost;
//                 pq.push({ny, nx, nextcost});
//             }
//         }
//     }
// }

// int main()
// {
//     freopen("input.txt", "r", stdin);
//     cin >> N >> A >> B;

//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             char tmp;
//             cin >> tmp;

//             if (tmp == '(')
//             {
//                 field[i][j] = 1;
//             }
//             else
//             {
//                 field[i][j] = 2;
//             }
//         }
//     }

//     int maxfuel = 0;

//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             for (int ii = 0; ii < N; ii++)
//             {
//                 for (int jj = 0; jj < N; jj++)
//                 {
//                     if (i == ii && j == jj)
//                         continue;

//                     maxfuel = max(maxfuel, dijkstra(i, j, ii, jj));
//                 }
//             }
//         }
//     }

//     cout << maxfuel << endl;
//     return 0;
// }

// the above code hits time limit

#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Edge
{
    int y;
    int x;
    int cost;
    bool operator<(Edge o) const
    {
        if (cost < o.cost)
            return false;
        if (cost > o.cost)
            return true;
        return false;
    }
};

int N, A, B;
string map[31];
int dist[31][31];

int ydir[] = {-1, 1, 0, 0};
int xdir[] = {0, 0, -1, 1};
int c = 0;

int dijkstra(int y, int x)
{
    c++;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dist[i][j] = 21e8;
    dist[y][x] = 0;

    priority_queue<Edge> pq;
    pq.push({y, x, 0});

    int res = -21e8;

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();

        if (dist[now.y][now.x] < now.cost)
            continue;

        res = max(res, dist[now.y][now.x]);

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                continue;

            int nc = 0;

            if (map[ny][nx] == map[now.y][now.x])
                nc = now.cost + A;
            else
                nc = now.cost + B;

            if (dist[ny][nx] <= nc)
                continue;
            dist[ny][nx] = nc;
            pq.push({ny, nx, nc});
        }
    }
    return res;
}

int main()
{
    cin >> N >> A >> B;
    for (int i = 0; i < N; i++)
        cin >> map[i];

    int res = -21e8;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            res = max(res, dijkstra(i, j));

    cout << res;
    return 0;
}