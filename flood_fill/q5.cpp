#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int height, width;
int ry, rx, by, bx;
int N;
int board[101][101];
struct Pos
{
    int y;
    int x;
};
Pos jjol[51];
int visited[101][101];

void input()
{
    // freopen("input.txt", "r", stdin);
    cin >> height >> width;

    cin >> ry >> rx >> by >> bx;

    cin >> N;

    memset(board, 0, sizeof(board));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < N; i++)
    {
        int y, x;
        cin >> y >> x;

        jjol[i] = {y, x};
        board[y][x] = 1;
    }
}

int bfs(int y, int x)
{
    queue<Pos> q;
    q.push({y, x});
    visited[y][x] = 0;

    while (!q.empty())
    {
        Pos now = q.front();
        q.pop();

        int ydir[] = {-3, -3, -2, 2, 3, 3, 2, -2};
        int xdir[] = {2, -2, -3, -3, -2, 2, 3, 3};

        for (int i = 0; i < 8; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= height || nx >= width)
                continue;

            if (visited[ny][nx])
                continue;

            if (board[ny][nx] == 1)
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ny, nx});

            if (ny == by && nx == bx)
            {
                return visited[ny][nx];
            }
        }
    }
    return -1;
}

int main()
{
    input();

    int ans = bfs(ry, rx);

    cout << ans;
    return 0;
}