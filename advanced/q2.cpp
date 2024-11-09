#include <iostream>
#include <cstring>

using namespace std;

int board[51][51];
int eaten[51][51];
int cnt;
int N;
int sy, sx;

int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void dfs(int level, int y, int x)
{
    if (level == 4)
    {
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        int length = 1;
        int skipped = 0;

        while (1)
        {
            int ny = y + dir[i][0] * length;
            int nx = x + dir[i][1] * length;

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                break;

            if (board[ny][nx] == 1)
                skipped++;

            if (skipped >= 3)
                break;

            if (skipped == 2 && board[ny][nx] == 1)
            {
                if (!eaten[ny][nx])
                {
                    cnt++;
                    eaten[ny][nx] = 1;
                }
                board[ny][nx] = 2;
                board[y][x] = 0;
                dfs(level + 1, ny, nx);
                board[ny][nx] = 1; // 여기 디버깅 해줘야 했음.
                // 왜냐하면 0으로 되돌리는 것이 아니라 1로 되돌려 줘야 하기 때문임.
                // backtracking 주의할 것!
                board[y][x] = 2;
            }

            if (skipped == 1 && board[ny][nx] == 0)
            {
                board[ny][nx] = 2;
                board[y][x] = 0;
                dfs(level + 1, ny, nx);
                board[ny][nx] = 0;
                board[y][x] = 2;
            }

            length++;
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N;
        memset(board, 0, sizeof(board));
        memset(eaten, 0, sizeof(eaten));
        cnt = 0;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> board[i][j];

                if (board[i][j] == 2)
                {
                    sy = i;
                    sx = j;
                }
            }
        }

        dfs(1, sy, sx);

        cout << "#" << tc << " " << cnt << '\n';
    }
}