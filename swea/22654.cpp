#include <iostream>
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

        cy = sy;
        cx = sx;

        for (int l = 0; l < len; l++)
        {
            char alphabet = cmd[tc][l];

            if (alphabet == 'R')
            {
                int cd = field[cy][cx];
                field[cy][cx] = dir[cd][1];
            }
            else if (alphabet == 'L')
            {
                int cd = field[cy][cx];
                field[cy][cx] = dir[cd][0];
            }
            else if (alphabet == 'A')
            {
                int pos = field[cy][cx];
                cy = cy + go[pos][0];
                cx = cx + go[pos][1];

                if (field[cy][cx] < 0)
                {
                    continue;
                }

                field[cy][cx] = pos;
            }
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
        for (int qc = 1; qc <= Q; qc++)
        {
            cin >> M[qc];

            cin >> cmd[qc];
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