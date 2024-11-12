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
            // green[i][j] 가 아님..
            if (block[i][j] == 1)
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
    // 초록색 도형의 최상단, 좌측 가장자리를 구합니다
    pair<int, int> minRC = minPoint(block); // 도형의 최소 위치
    pair<int, int> maxRC = maxPoint(block); // 도형의 최대 위치

    // 배치할 수 있는 공간이 판의 범위 내에 있는지 확인
    if (y + maxRC.first > 9 || x + maxRC.second > 9)
    {
        return false; // 도형이 판 밖으로 벗어날 경우
    }

    // 배치할 공간에 벽이나 다른 도형이 있는지 확인
    for (int i = 0; i <= maxRC.first - minRC.first; i++)
    {
        for (int j = 0; j <= maxRC.second - minRC.second; j++)
        {
            if (block[i][j] == 1)
            { // 초록색 블럭이 있을 경우
                if (board[y + i][x + j] == -1)
                {
                    return false; // 해당 칸에 이미 도형이 있거나 벽이 있을 경우
                }
            }
        }
    }

    // 배치 가능한 경우, 해당 공간을 사용 표시
    for (int i = 0; i <= maxRC.first - minRC.first; i++)
    {
        for (int j = 0; j <= maxRC.second - minRC.second; j++)
        {
            if (block[i][j] == 1)
            {
                used[y + i][x + j] = 1; // 해당 칸을 사용했다고 표시
            }
        }
    }

    return true; // 도형을 배치할 수 있음
}

// Function to print a 4x4 block
void printBlock(const vector<vector<int>> &block)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << block[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);

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

    for (int i = 1; i < 4; i++)
    {
        shapeVariation[i] = rotate(shapeVariation[i - 1]);
        shift(shapeVariation[i]);
    }

    // // Print out all the rotated variations for debugging
    // cout << "Shape variations after rotation:" << endl;
    // for (int i = 0; i < 5; i++)
    // {
    //     cout << "Rotation " << i << ":" << endl;
    //     printBlock(shapeVariation[i]);
    // }

    // now find all the empty spots in the board that can fit in the green shapes
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int idx = 0; idx < 4; idx++)
            {
                if (idx == 2 && shapeVariation[0] == shapeVariation[2])
                    continue;

                if (idx == 3 && shapeVariation[1] == shapeVariation[3])
                    continue;

                if (idx == 1 && shapeVariation[0] == shapeVariation[1])
                    continue;

                if (fitting(i, j, shapeVariation[idx]))
                {
                    cnt++;
                }
            }
        }
    }

    cout << cnt << '\n';

    // for (int i = 0; i < 10; i++)
    // {
    //     for (int j = 0; j < 10; j++)
    //     {
    //         cout << used[i][j] << " ";
    //     }
    //     cout << '\n';
    // }

    return 0;
}