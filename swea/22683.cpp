#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int T;
int N, K;
int field[11][11];
int used[11][11][6][4];
int sy, sx;
int dy, dx;

// 0 = y; 1 = x;
int go[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}};

// 0 = L; 1 = R;
int direct[4][2] = {
    {1, 3},
    {2, 0},
    {3, 1},
    {0, 2}};

struct pos
{
    int y;
    int x;
    int cnt;
    int dir;
    int k;
};

int explore()
{
    queue<pos> q;
    q.push({sy, sx, 0, 0, K});
    used[sy][sx][K][0] = 1;

    while (!q.empty())
    {
        pos now = q.front();
        q.pop();

        if (now.y == dy && now.x == dx)
        {
            return now.cnt;
        }

        int nd = direct[now.dir][0];
        q.push({now.y, now.x, now.cnt + 1, nd, K});
        used[now.y][now.x][K][nd] = 1;

        nd = direct[now.dir][1];
        q.push({now.y, now.x, now.cnt + 1, nd, K});
        used[now.y][now.x][K][nd] = 1;

        int ny = now.y + go[now.dir][0];
        int nx = now.x + go[now.dir][1];

        if (ny < 0 || nx < 0 || ny >= N || nx >= N || used[ny][nx])
            continue;
        if (field[ny][nx] == -1 && K < 0)
        {
            continue;
        }

        if (field[ny][nx] == -1)
        {
            K--;
            field[ny][nx] = 0;
        }
        q.push({ny, nx, now.cnt + 1, now.dir, K});
        used[ny][nx][K][now.dir] = 1;
    }
    return -1;
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N >> K;

        memset(field, 0, sizeof(field));
        memset(used, 0, sizeof(used));

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                char c;
                cin >> c;

                if (c == 'G')
                {
                    field[i][j] = 0;
                }
                else if (c == 'T')
                {
                    field[i][j] = -1;
                }
                else if (c == 'X')
                {
                    field[i][j] = 0;
                    sy = i;
                    sx = j;
                }
                else if (c == 'Y')
                {
                    field[i][j] = 0;
                    dy = i;
                    dx = j;
                }
            }
        }

        int ans = explore();

        cout << "#" << tc << " " << ans << endl;
    }
}