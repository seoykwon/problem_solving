#include <iostream>
#include <cstring>
using namespace std;

int T, N, Q;
int field[5][5];
int sy, sx;
int cy, cx;
int dy, dx;
int M[5];
char cmd[5][51];
int res[5];

// 0 = L
// 1 = R
int dir[4][2] = {
    {1, 3},
    {2, 0},
    {3, 1},
    {0, 2}};

// 0 = y
// 1 = x
int go[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}};

void explore()
{
    for (int tc = 0; tc < Q; tc++)
    {
        int len = M[tc];
        int cd = 0;

        cy = sy;
        cx = sx;

        for (int l = 0; l < len; l++)
        {
            char alphabet = cmd[tc][l];

            if (alphabet == 'R')
            {
                // int cd = field[cy][cx];
                // field[cy][cx] = dir[cd][1];
                cd = dir[cd][1];
            }
            else if (alphabet == 'L')
            {
                // int cd = field[cy][cx];
                // field[cy][cx] = dir[cd][0];
                cd = dir[cd][0];
            }
            else if (alphabet == 'A')
            {
                int ny = cy + go[cd][0];
                int nx = cx + go[cd][1];

                if (field[ny][nx] == -1)
                {
                    continue;
                }

                if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                    continue;

                cy = ny;
                cx = nx;
            }
        }
        if (cy == dy && cx == dx)
        {
            res[tc] = 1;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        memset(field, 0, sizeof(field));
        memset(M, 0, sizeof(M));
        memset(res, 0, sizeof(res));
        cin >> N;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                char ch;
                cin >> ch;

                if (ch == 'G')
                {
                    field[i][j] = 0;
                }
                else if (ch == 'X')
                {
                    field[i][j] = 0;
                    sy = i;
                    sx = j;
                }
                else if (ch == 'T')
                {
                    field[i][j] = -1;
                }
                else if (ch == 'Y')
                {
                    field[i][j] = 0;
                    dy = i;
                    dx = j;
                }
            }
        }

        cin >> Q;
        for (int qc = 0; qc < Q; qc++)
        {
            cin >> M[qc];

            cin >> cmd[qc];

            // cout << "cmd: " << cmd[qc] << " ";
        }

        explore();

        cout << "#" << tc << " ";
        for (int f = 0; f < Q; f++)
        {
            cout << res[f] << " ";
        }
        cout << endl;
    }
}

// key debugging issues:
// 1. separate direction variables : the cd var maintains the current facing dir of the car
// 2. boundary checking before movement: the potential next pos is checked before moving to it
