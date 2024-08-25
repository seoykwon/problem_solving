#include <iostream>
#include <queue>
using namespace std;

int board[4][4] = {0};
struct Node
{
    int y;
    int x;
};
int visited[4][4] = {0};
int sizeIsland = 0;

int bfs(int sy, int sx)
{
    queue<Node> q;
    q.push({sy, sx});
    visited[sy][sx] = 1;
    sizeIsland = 1;

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

            if (visited[ny][nx])
                continue;

            if (board[ny][nx] == 0)
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            sizeIsland++;
            q.push({ny, nx});
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> board[i][j];
        }
    }

    bfs(0, 0);

    // int island = 0;
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         if (island < visited[i][j])
    //         {
    //             island = visited[i][j];
    //         }
    //     }
    // }
    cout << sizeIsland;
    return 0;
}