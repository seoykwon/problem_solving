#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
char type;
int board[201][201];
int visited[201][201];
int anum, bnum, maxnum;
struct pos
{
    int y;
    int x;
};

void input()
{
    // freopen("input.txt", "r", stdin);
    cin >> N >> M;

    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char tmp;
            cin >> tmp;

            if (tmp == '_')
            {
                board[i][j] = -1;
            }
            else
            {
                board[i][j] = int(tmp - 'A');
            }
        }
    }
}

void bfs(int y, int x, int type)
{
    queue<pos> q;
    q.push({y, x});
    visited[y][x] = 1;
    int cnt = 1;

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

            if (board[ny][nx] != type)
                continue;

            cnt++;
            visited[ny][nx] = 1;
            q.push({ny, nx});
        }
    }
    maxnum = max(maxnum, cnt);
    if (type == 0)
    {
        anum++;
    }
    else
    {
        bnum++;
    }
}

int main()
{
    input();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] != -1 && !visited[i][j])
            {
                bfs(i, j, board[i][j]);
            }
        }
    }

    cout << anum << " " << bnum << endl;
    cout << maxnum << endl;
    return 0;
}