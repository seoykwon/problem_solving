#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int T, N;
int board[51][51];
int cnt = 0;
int po_x = 0;
int po_y = 0;
int visited[51][51] = {
    0,
};

void input()
{
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            board[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> board[i][j];

            if (board[i][j] == 2)
            {
                po_y = i;
                po_x = j;
                board[i][j] = 0;
            }
        }
    }
}

void dfs(int y, int x, int trial)
{

    if (trial == 4)
    {
        return;
    }
    if (board[y][x] == 1)
    {

        // cout << "eat jjol: " << y << " " << x << endl;
        cnt++;
        // cout << "cnt: " << cnt << endl;
        board[y][x] = 3;
        return;
    }
    int ydir[4] = {-1, 0, 1, 0};
    int xdir[4] = {0, -1, 0, 1};

    for (int i = 0; i < 4; i++)
    {
        bool can_j = false;
        for (int j = 1; j < N; j++)
        {
            int ny = y + ydir[i] * j;
            int nx = x + xdir[i] * j;

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                break;

            if ((board[ny][nx] == 1 || board[ny][nx] == 3) && !can_j)
            {
                // int nny = y + ydir[i] * (j + 1);
                // int nnx = x + xdir[i] * (j + 1);

                // if (nny < 0 || nnx < 0 || nny >= N || nnx >= N)
                //     break;

                // if (board[nny][nnx] == 0)
                // {
                //     can_j = true;
                // }
                can_j = true;
                continue;
            }

            if (can_j)
            {
                cout << ny << " " << nx << " trial: " << trial << endl;
                dfs(ny, nx, trial + 1);
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        input();

        dfs(po_y, po_x, 0);

        cout << "#" << t << " " << cnt << endl;
    }
}
