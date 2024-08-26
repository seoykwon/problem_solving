#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

int N, M;
int board[11][11];
struct pos
{
    int y;
    int x;
};
pos cur = {0, 0};
int dist[11][11];

void input()
{
    cin >> N >> M;
    // cout << N << " " << M << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            // cout << "hello" << endl;
            char tmp;
            cin >> tmp;
            // cout << tmp << endl;

            if (tmp == '#')
            {
                // cout << "here" << endl;
                board[i][j] = -1;
            }
            else
            {
                // cout << int(tmp - '0') << endl;
                board[i][j] = int(tmp - '0');
            }
            // cout << board[i][j];
        }
        // cout << endl;
    }
}

int bfs(int sy, int sx, int target)
{
    queue<pos> q;
    dist[sy][sx] = 0;
    q.push({sy, sx});

    while (!q.empty())
    {
        pos now = q.front();
        q.pop();

        int ydir[] = {-1, 0, 1, 0};
        int xdir[] = {0, -1, 0, 1};

        // target is on the current node
        // needs to cover this case in order to pass all the tests
        if (board[now.y][now.x] == target)
        {
            cur.y = now.y;
            cur.x = now.x;
            return dist[now.y][now.x];
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;

            // if (dist[ny][nx] < dist[now.y][now.x] + 1)
            //     continue;
            // we are planning to find the target, not flood fill. we do not need to exclude distance

            if (board[ny][nx] == -1)
                continue;

            dist[ny][nx] = dist[now.y][now.x] + 1;

            if (board[ny][nx] == target)
            {
                cur.y = ny;
                cur.x = nx;
                return dist[ny][nx];
            }
            q.push({ny, nx});
        }
    }

    return 0;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    input();

    int ans = 0;

    cur = {0, 0};
    for (int i = 1; i < 5; i++)
    {
        // memset(dist, 21e8, sizeof(dist));
        // 21e8 is bigger than int container, so it keeps initializing dist as 0
        memset(dist, INT_MAX, sizeof(dist));
        ans += bfs(cur.y, cur.x, i);
    }

    cout << ans << "회";
    return 0;
}
