#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int m, n;
int box[1001][1001] = {
    0,
};
int used[1001][1001] = {
    0,
};
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

struct node
{
    int y, x;
    int cnt;
};
queue<node> q;

int bfs()
{
    int ans = 0;

    while (!q.empty())
    {
        node now = q.front();
        q.pop();
        ans = max(ans, now.cnt);

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dir[i][0];
            int nx = now.x + dir[i][1];

            if (ny < 0 || nx < 0 || ny >= n || nx >= m || used[ny][nx])
                continue;

            if (box[ny][nx] != 0)
                continue;

            used[ny][nx] = 1;
            box[ny][nx] = 1;
            q.push({ny, nx, now.cnt + 1});
        }
    }

    return ans;
}

int main()
{
    // freopen("input.txt", "r", stdin);

    cin >> m >> n;

    int y, x;

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> box[i][j];

            if (box[i][j] == 1)
            {
                q.push({i, j, 0});
            }
        }
    }

    ans = bfs();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (box[i][j] == 0)
            {
                ans = -1;
            }
            // cout << box[i][j] << " ";
        }
        // cout << endl;
    }

    cout << ans << '\n';
    return 0;
}