#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> green(4, vector<int>(4, 0));
int board[10][10] = {
    0,
};
int used[10][10] = {
    0,
};
int cnt = 0;
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

vector<vector<int>> shapeVariation[4];

pair<int, int> maxPoint(const vector<vector<int>> &block)
{
    int y = 0;
    int x = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (green[i][j] == 1)
            {
                y = max(y, i);
                x = max(x, j);
            }
        }
    }

    pair<int, int> ret = make_pair(y, x);
    return ret;
}

pair<int, int> minPoint(const vector<vector<int>> &block)
{
    int y = 4;
    int x = 4;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // green[i][j] 가 아님!!!!
            if (block[i][j] == 1)
            {
                y = min(y, i);
                x = min(x, j);
            }
        }
    }

    pair<int, int> ret = make_pair(y, x);
    return ret;
}

void shift(vector<vector<int>> &block)
{
    vector<vector<int>> tmp(4, vector<int>(4, 0));

    pair<int, int> minRC = minPoint(block);
    int f = minRC.first, s = minRC.second;

    for (int i = 0; i + f < 4; i++)
    {
        for (int j = 0; j + s < 4; j++)
        {
            tmp[i][j] = block[i + f][j + s];
        }
    }
    block = tmp;
}

vector<vector<int>> rotate(const vector<vector<int>> &block)
{
    vector<vector<int>> res(4, vector<int>(4, 0));

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res[j][3 - i] = block[i][j];
        }
    }

    return res;
}

bool fitting(int y, int x, vector<vector<int>> &block)
{
    pair<int, int> maxRC = maxPoint(block);

    int f = maxRC.first;
    int s = maxRC.second;

    for (int i = 0; i <= f; i++)
    {
        for (int j = 0; j <= s; j++)
        {
            if (block[i][j] == 1)
            {
                if (board[y + i][x + j] != 0 || used[y + i][x + j])
                {
                    return false;
                }
            }
        }
    }

    // reaching here means that the block fits in
    for (int i = 0; i <= f; i++)
    {
        for (int j = 0; j <= s; j++)
        {
            if (block[i][j] == 1)
            {
                used[y + i][x + j] = 1;
            }
        }
    }

    return true;
}

int main()
{
    freopen("input.txt", "r", stdin);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            char tmp;
            cin >> tmp;

            green[i][j] = (tmp == '$') ? 1 : 0;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            char tmp;
            cin >> tmp;

            board[i][j] = (tmp == '_') ? 0 : -1;
        }
    }

    shift(green);

    shapeVariation[0] = green;

    for (int i = 1; i <= 3; i++)
    {
        shapeVariation[i] = rotate(shapeVariation[i - 1]);
    }

    // now find all the empty spots in the board that can fit in the green shapes
    for (int i = 0; i <= 10 - 4; i++)
    {
        for (int j = 0; j <= 10 - 4; j++)
        {
            for (int idx = 0; idx < 4; idx++)
            {
                if (fitting(i, j, shapeVariation[idx]))
                {
                    cnt++;
                }
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
