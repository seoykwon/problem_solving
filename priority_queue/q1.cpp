#include <iostream>
#include <queue>
#include <climits>
using namespace std;

int sy, sx;
int field[5][5];
struct pos
{
    int y;
    int x;
};
int dist[5][5];

void bfs(int y, int x)
{
    queue<pos> q;
    q.push({y, x});
    dist[y][x] = 1;

    while (!q.empty())
    {
        pos now = q.front();
        q.pop();

        int ydir[] = {-1, 0, 1, 0};
        int xdir[] = {0, -1, 0, 1};

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 5 || nx >= 5)
                continue;

            if (dist[ny][nx] < dist[now.y][now.x] + 1)
                continue;

            dist[ny][nx] = dist[now.y][now.x] + 1;

            q.push({ny, nx});
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> sy >> sx;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            dist[i][j] = INT_MAX;
        }
    }

    bfs(sy, sx);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}