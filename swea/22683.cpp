#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int T, N, K;
int field[11][11];
int used[11][11][6][4];
int sy, sx, dy, dx, cy, cx;

struct pos
{
    int y;
    int x;
    int cnt;
    int k;
    int d;
};

// 0 = y; 1 = x;
int dir[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}};

int explore()
{
    queue<pos> q;
    q.push({sy, sx, 0, K, 0});
    used[sy][sx][K][0] = 1;

    while (!q.empty())
    {
        pos now = q.front();
        q.pop();

        if (now.y == dy && now.x == dx)
        {
            // cout << "here" << now.cnt << endl;
            return now.cnt;
        }

        // cout << now.cnt << endl;
        // turn left
        int ld = now.d;
        ld = (now.d + 1) % 4;
        if (!used[now.y][now.x][now.k][ld])
        {
            q.push({now.y, now.x, now.cnt + 1, now.k, ld});
            used[now.y][now.x][now.k][ld] = 1;
        }

        // turn right
        int rd = (now.d + 3) % 4;
        if (!used[now.y][now.x][now.k][rd])
        {
            q.push({now.y, now.x, now.cnt + 1, now.k, rd});
            used[now.y][now.x][now.k][rd] = 1;
        }

        // int ny = now.y + dir[now.k][0];
        // int nx = now.x + dir[now.k][1];
        int ny = now.y + dir[now.d][0];
        int nx = now.x + dir[now.d][1];

        // this line occurred zsh: bus error bc it accessed memory unsafely
        // if (ny >= 0 || nx >= 0 || ny < N || nx < N || !used[ny][nx][now.k][now.d])
        if (ny >= 0 && nx >= 0 && ny < N && nx < N && !used[ny][nx][now.k][now.d])
        {

            if (field[ny][nx] == 0)
            {
                used[ny][nx][now.k][now.d] = true;
                q.push({ny, nx, now.cnt + 1, now.k, now.d});
            }
            else if (field[ny][nx] == -1 && now.k > 0)
            {
                used[ny][nx][now.k - 1][now.d] = true;
                q.push({ny, nx, now.cnt + 1, now.k - 1, now.d});
            }
        }
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
                    sy = i;
                    sx = j;
                    field[i][j] = 0;
                }
                else if (c == 'Y')
                {
                    dy = i;
                    dx = j;
                    field[i][j] = 0;
                }
            }
        }

        int ans = explore();

        cout << "#" << tc << " " << ans << endl;
    }
}

// debugging done!
// make sure you use boundary correctly
// when using struct, you need to check you are pushing the elements in right order
