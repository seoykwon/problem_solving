#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int field[101][101];
int dist[101][101];
int dir[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}};

struct Pos
{
    int y;
    int x;
    int w;

    bool operator<(Pos right) const
    {
        if (w < right.w)
            return false;
        if (w > right.w)
            return true;
        return false;
    }
};
int used[101][101];

void dijkstra(int sy, int sx)
{
    priority_queue<Pos> pq;

    pq.push({sy, sx, field[sy][sx]});

    while (!pq.empty())
    {
        Pos now = pq.top();
        pq.pop();

        if (now.y == N - 1 && now.x == M - 1)
        {
            cout << now.w;
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dir[i][0];
            int nx = now.x + dir[i][1];

            if (ny < 0 || ny >= N || nx < 0 || nx >= M || used[ny][nx])
                continue;

            pq.push({ny, nx, now.w + field[ny][nx]});
            used[ny][nx] = 1;
        }
    }
}

int main()
{
    memset(field, 0, sizeof(field));
    memset(used, 0, sizeof(used));

    // freopen("input.txt", "r", stdin);

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> field[i][j];
        }
    }

    dijkstra(0, 0);

    return 0;
}

// ###################################
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
int MAP[100][100];

int ydir[] = {0, 0, 1, -1};
int xdir[] = {1, -1, 0, 0};

struct Node
{
    int y;
    int x;
    int cost;
};

bool operator<(Node a, Node b)
{
    if (a.cost < b.cost)
        return false;
    if (a.cost > b.cost)
        return true;
    return false;
}

void dijkstra(int y, int x)
{
    priority_queue<Node> pq;
    pq.push({y, x, MAP[y][x]});

    int dist[100][100] = {
        0,
    };
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            dist[i][j] = 2134567890;
        }
    }
    dist[y][x] = MAP[y][x];

    while (!pq.empty())
    {
        Node now = pq.top();
        pq.pop();

        if (dist[now.y][now.x] < now.cost)
            continue;

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= n || nx >= m)
                continue;

            int nextcost = dist[now.y][now.x] + MAP[ny][nx];

            if (dist[ny][nx] <= nextcost)
                continue;

            dist[ny][nx] = nextcost;
            pq.push({ny, nx, dist[ny][nx]});
        }
    }
    cout << dist[n - 1][m - 1];
}

int main()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> MAP[i][j];
        }
    }

    dijkstra(0, 0);
}