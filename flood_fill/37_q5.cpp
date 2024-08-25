#include <iostream>
#include <queue>
using namespace std;

int visited[4][4];
int board[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 0, 1},
    {0, 0, 0, 0},
    {1, 0, 1, 0}};
struct Node
{
    int y;
    int x;
};
int sy, sx;
int fy, fx;

void bfs(int y, int x)
{
    queue<Node> q;
    q.push({y, x});
    visited[y][x] = 1;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        int ydir[] = {-1, 0, 1, 0};
        int xdir[] = {0, -1, 0, 1};

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4)
                continue;
            if (board[ny][nx] == 1 || visited[ny][nx])
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ny, nx});
        }
    }
}

int main()
{
    cin >> sy >> sx >> fy >> fx;

    bfs(sy, sx);

    cout << visited[fy][fx] - 1 << "회";
    return 0;
}

// ######### 강사님 코드 #################
#include <iostream>
#include <queue>
using namespace std;

int map[4][5] = {
    0,
    0,
    0,
    0,
    1,
    1,
    0,
    1,
    0,
    0,
    0,
    0,
    1,
    0,
    1,
    0,
};
int used[4][4];
struct Node
{
    int y;
    int x;
    int level;
};
int h, t;
Node q[11000];

int bfs()
{
    int direct[4][2] = {-1, 0, 1, 0, 0, 1, 0, -1};

    int a, b;
    int tarY, tarX;

    cin >> a >> b;
    cin >> tarY >> tarX;

    q[t++] = {a, b, 0};
    used[a][b] = 1;

    while (h != t)
    {
        Node now = q[h++];
        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + direct[i][0];
            int nx = now.x + direct[i][1];

            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4)
                continue;
            if (map[ny][nx] == 1 || used[ny][nx] == 1)
                continue;

            used[ny][nx] = 1;

            q[t++] = {ny, nx, now.level + 1};

            if (ny == tarY && nx == tarX)
            {
                return now.level + 1;
            }
        }
    }

    return -1;
}

int main()
{
    int ret = bfs();
    cout << ret << "회";

    return 0;
}