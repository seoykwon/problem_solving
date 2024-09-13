#include <iostream>

using namespace std;

int n;
int board[8][8];
// 1 = black 2 = white
int dat[8] = {7, 6, 5, 4, 3, 2, 1, 0};

void colorcheck()
{
}

void play(int y, int x, int color)
{
    // change the index of y
    int ny = dat[y];

    board[ny][x] = color;

    colorcheck();
}

int main()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = 0;
        }
    }

    freopen("input.txt", "r", stdin);
    cin >> n;

    int black = 0;

    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;

        if (i % 2 == 0)
        {
            black = 2;
        }
        else
        {
            black = 1;
        }

        play(y, x, black);
    }
}