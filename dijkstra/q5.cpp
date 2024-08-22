#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int y, x;
int n;
int town[1001][1001] = {
    0,
};
int maxCnt = 0;
int dist[1001][1001];

struct Edge
{
    int y;
    int x;
    int cost;

    bool operator<(Edge right) const
    {
        return cost > right.cost;
    }
};

void dijkstra(int y, int x)
{
    priority_queue<Edge> q;
    q.push({y, x, town[y][x]});
    dist[y][x] = town[y][x];

    int ydir[4] = {-1, 0, 1, 0};
    int xdir[4] = {0, -1, 0, 1};

    while (!q.empty())
    {
        Edge now = q.top();
        q.pop();

        if (dist[now.y][now.x] < now.cost)
            continue;
        // 불필요한 작업임

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= n || nx >= n || town[ny][nx] == -1)
                continue;

            int nextcost = now.cost + town[ny][nx];

            // 하지만 이 작업은 꼭 필요함
            // 최단 거리만을 가려면 이 조건문이 존재해야 함
            if (nextcost < dist[ny][nx])
            {
                dist[ny][nx] = nextcost;
                q.push({ny, nx, nextcost});
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> y >> x;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> town[i][j];
            dist[i][j] = 21e8;
        }
    }

    dijkstra(y, x);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // 초기값을 제외해 주는 부분이 중요함
            if (maxCnt < dist[i][j] && dist[i][j] != 21e8)
            {
                maxCnt = dist[i][j];
            }
        }
    }

    cout << maxCnt;
}
