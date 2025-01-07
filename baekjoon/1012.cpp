#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

int field[51][51] = {
    0,
};
int visited[51][51] = {
    0,
};
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int ans = 0;

void bfs(int y, int x, int m, int n)
{
    queue<pair<int, int>> q;
    q.push(make_pair(y, x));

    while (!q.empty())
    {
        pii now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = now.first + dir[i][0];
            int nx = now.second + dir[i][1];

            if (ny < 0 || nx < 0 || ny >= n || nx >= m || visited[ny][nx])
                continue;

            if (field[ny][nx] == 1)
            {
                visited[ny][nx] = 1;
                q.push(make_pair(ny, nx));
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int t;
    cin >> t;

    while (t--)
    {
        memset(field, 0, sizeof(field));
        memset(visited, 0, sizeof(visited));
        ans = 0;
        int m, n, k;
        cin >> m >> n >> k;

        for (int i = 0; i < k; i++)
        {
            int x, y;
            cin >> x >> y;

            field[y][x] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (visited[i][j] == 0 && field[i][j] == 1)
                {
                    bfs(i, j, m, n);
                    ans++;
                }
            }
        }

        cout << ans << '\n';
    }
}