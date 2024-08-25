#include <iostream>
#include <queue>
using namespace std;

int board[4][6];
int meat = 0;
int visited[4][6];
struct Node
{
    int y;
    int x;
};

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

            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 6)
                continue;
            if (visited[ny][nx] || board[ny][nx] == 1)
                continue;

            if (board[ny][nx] == 2)
                meat++;

            visited[ny][nx] = 1;
            q.push({ny, nx});
        }
    }
}

int main()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cin >> board[i][j];
        }
    }

    bfs(0, 0);

    cout << meat;
}