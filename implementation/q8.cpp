#include <iostream>

using namespace std;

int N;
char d;
int s;
int canvas[6][6];

void color()
{
    int sy = 5;
    int sx = s;
    int intensity = 1;
    canvas[sy][sx] = intensity;

    if (d == 'R')
    {
        int yd = -1;
        int xd = 1;

        int ny = sy;
        int nx = sx;

        while (true)
        {
            ny = ny + yd;
            nx = nx + xd;

            if (nx >= 6)
            {
                xd = -1;
                nx = nx + xd - 1;
            }
            else if (ny < 0)
            {
                yd = 1;
                ny = ny + yd + 1;
            }
            else if (nx < 0)
            {
                xd = 1;
                nx = nx + xd + 1;
            }

            if (ny < 0 || nx < 0 || ny >= 6 || nx >= 6)
            {
                break;
            }

            ++intensity;
            if (canvas[ny][nx] == 0 || canvas[ny][nx] > intensity)
            {
                canvas[ny][nx] = intensity;
            }

            if (intensity == 10)
            {
                break;
            }
        }
    }
    else if (d == 'L')
    {
        int yd = -1;
        int xd = -1;

        int ny = sy;
        int nx = sx;

        while (true)
        {
            ny = ny + yd;
            nx = nx + xd;

            if (nx >= 6)
            {

                xd = -1;
                nx = nx + xd - 1;
            }
            else if (ny < 0)
            {

                yd = 1;
                ny = ny + yd + 1;
            }
            else if (nx < 0)
            {

                xd = 1;
                nx = nx + xd + 1;
            }

            if (ny < 0 || nx < 0 || ny >= 6 || nx >= 6)
            {
                break;
            }

            ++intensity;
            if (canvas[ny][nx] == 0 || canvas[ny][nx] > intensity)
            {
                canvas[ny][nx] = intensity;
            }

            if (ny == 6)
            {
                break;
            }
        }
    }
}

int main()
{

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            canvas[i][j] = 0;
        }
    }

    // freopen("input.txt", "r", stdin);
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        cin >> s >> d;

        color();
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (canvas[i][j] == 0)
            {
                cout << '_';
            }
            else
            {
                cout << canvas[i][j];
            }
        }
        cout << endl;
    }
}

// ########## 강사님 코드 #############
// 나는 왜 이렇게 꼬아서 풀었지?
// 방향 배열 문제이면 간단하게 방향배열을 사용하면 됐었는데!

#include <iostream>
#include <vector>
using namespace std;

int Canvas[6][6];

int dir[2][4][2] = {
    {{-1, 1},
     {-1, -1},
     {1, -1},
     {1, 1}},
    {{-1, -1},
     {-1, 1},
     {1, 1},
     {1, -1}}};

void blast(int cur, char direction)
{
    int d = 0;
    if (direction == 'R')
        d = 0;
    else
        d = 1;

    int num = 2;
    int y = 5; // 항상 바닥부터
    int x = cur;

    Canvas[y][x] = 1;
    int flag = 0;

    for (int i = 0; i < 4; i++)
    {
        while (true)
        {
            int ny = y + dir[d][i][0];
            int nx = x + dir[d][i][1];
            if (ny < 0 || nx < 0 || ny >= 6 || nx >= 6)
            {
                break;
            }
            // 만약 지금 숫자가 더 크면
            if (Canvas[ny][nx] != 0)
            {
                // 덮어씌운다
                if (num < Canvas[ny][nx])
                    Canvas[ny][nx] = num;
            }
            // 빈칸이면 그대로 print
            else
                Canvas[ny][nx] = num;

            // 좌표 이동
            num++;
            y = ny;
            x = nx;
        }
    }
}

int main()
{
    // input
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int num;
        char direction;
        cin >> num >> direction;
        // solve
        blast(num, direction);
    }

    // print
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (Canvas[i][j] == 0)
                cout << "_";
            else
                cout << Canvas[i][j];
        }
        cout << '\n';
    }
}
