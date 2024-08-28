#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int board[151][151];
int visited[151][151];
// 2 = 감염된 컴퓨터
struct pos
{
    int y;
    int x;
};

void input()
{
    // freopen("input.txt", "r", stdin);
    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> board[i][j];
        }
    }
    memset(visited, 0, sizeof(visited));

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < M; j++)
    //     {
    //         cout << visited[i][j] << " ";
    //     }
    // }
}

int bfs(int y, int x)
{
    queue<pos> q;
    q.push({y, x});
    visited[y][x] = 1;
    int flag = 0;

    if (board[y][x] == 2)
    {
        flag = 1;
    }

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

            if (ny < 0 || nx < 0 || ny >= N || nx >= M || visited[ny][nx])
                continue;

            if (board[ny][nx] == 0)
                continue;

            visited[ny][nx] = 1;
            q.push({ny, nx});

            if (board[ny][nx] == 2)
            {
                flag = 2;
            }
        }
    }
    // 이거 위치 조심!
    if (flag)
        return 1;

    return 0;
}

int main()
{
    input();

    int ans = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if ((board[i][j] == 1 || board[i][j] == 2) && !visited[i][j])
            {
                // cout << i << " " << j << endl;
                ans += bfs(i, j);
                // cout << ans << endl;
            }
        }
    }

    cout << ans;
    return 0;
}