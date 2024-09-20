#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int T;
int N;
int board[51][51] = {0};
int visited[51][51] = {0};
int sy, sx;
int ans = 0;

int yd[4] = {1, 0, -1, 0};
int xd[4] = {0, -1, 0, 1};

struct pos
{
    int y;
    int x;
};

void calculate(int y, int x, int trial)
{
    if (trial == 4)
    {
        return;
    }

    if (board[y][x] == 1)
    {
        // cout << "eat jjol: " << y << " " << x << endl;
        board[y][x] = 3;
        ans++;
    }

    for (int i = 0; i < 4; i++)
    {
        bool can_j = false;

        for (int j = 1; j < N; j++)
        {
            int ny = y + yd[i] * j;
            int nx = x + xd[i] * j;

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                break;

            if ((board[ny][nx] == 1 || board[ny][nx] == 3) && !can_j)
            {
                can_j = true;
                continue;
            }

            if (can_j)
            {
                // you cannot jump over 2 jjol at once:

                calculate(ny, nx, trial + 1);
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> T;

    for (int i = 1; i <= T; i++)
    {
        cin >> N;

        // need to reset the board and visited every time new test case is inputted
        memset(board, 0, sizeof(board));
        memset(visited, 0, sizeof(visited));
        ans = 0;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> board[i][j];

                if (board[i][j] == 2)
                {
                    sy = i;
                    sx = j;
                    board[i][j] = 0;
                }
            }
        }

        calculate(sy, sx, 0);

        cout << "#" << i << " " << ans << endl;
    }
}
