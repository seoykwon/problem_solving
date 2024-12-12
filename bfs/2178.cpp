#include <iostream>
#include <string>
#include <queue>

using namespace std;

int field[101][101] = {
    0,
};
int used[101][101] = {
    0,
};
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int ans = 0;

struct edge
{
    int y;
    int x;
    int cnt;
};

void bfs(int y, int x, int &n, int &m)
{
    queue<edge> q;
    q.push({y, x, 1});
    used[y][x] = 1;

    while (!q.empty())
    {
        edge now = q.front();
        q.pop();

        if (now.y == n - 1 && now.x == m - 1)
        {
            ans = now.cnt;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dir[i][0];
            int nx = now.x + dir[i][1];

            if (ny < 0 || nx < 0 || ny >= n || nx >= m || used[ny][nx])
                continue;

            if (field[ny][nx] == 1)
            {
                used[ny][nx] = 1;
                q.push({ny, nx, now.cnt + 1});
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        string row;
        cin >> row;

        for (int j = 0; j < m; j++)
        {
            field[i][j] = row[j] - '0';
        }
    }

    bfs(0, 0, n, m);

    cout << ans << '\n';
    return 0;
}