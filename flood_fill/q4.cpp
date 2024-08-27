#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

int height, width;
int board[101][101];
int ny, nx, ty, tx;
int ans = 0;

struct pos
{
    int y;
    int x;
};

int bfs(int y, int x)
{
    queue<pos> q;
    q.push({y, x});
    board[y][x] = 0;

    while (!q.empty())
    {
        pos now = q.front();
        q.pop();

        int ydir[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        int xdir[] = {-1, -2, -2, -1, 1, 2, 2, 1};

        for (int i = 0; i < 8; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= height || nx >= width)
                continue;

            if (board[ny][nx] <= board[now.y][now.x] + 1)
                continue;

            board[ny][nx] = board[now.y][now.x] + 1;

            if (ny == ty && nx == tx)
            {
                return board[ny][nx];
            }

            q.push({ny, nx});
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> height >> width;
    cin >> ny >> nx >> ty >> tx;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            board[i][j] = INT_MAX;
        }
    }

    ans = bfs(ny, nx);

    cout << ans;
}