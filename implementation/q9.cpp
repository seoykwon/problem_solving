#include <iostream>
#include <vector>

using namespace std;

// 0 = empty, 1 = black, 2 = white
int board[8][8] = {0};
// 상 좌 하 우 좌상 좌하 우상 우하
int dir[8][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};

// 색을 뒤집는 함수
void changeColor(int y, int x, int d_idx, int dist)
{
    int curColor = board[y][x];     // 현재 색
    for (int i = 1; i <= dist; i++) // 1부터 dist까지 변경
    {
        int ny = y + dir[d_idx][0] * i;
        int nx = x + dir[d_idx][1] * i;
        board[ny][nx] = curColor; // 색을 바꿈
    }
}

// 돌을 놓고 색을 변경하는 함수
void place(int idx, int y, int x)
{
    int curColor = (idx % 2 == 0) ? 2 : 1;  // 흑돌(1) 또는 백돌(2)
    board[y][x] = curColor;                 // 돌을 놓음
    int opposite = (curColor == 1) ? 2 : 1; // 반대 색

    // 4방향을 확인하면서 색을 뒤집을지 여부를 판단
    for (int i = 0; i < 8; i++)
    {
        int dist = 0;
        bool canFlip = false;

        // 한 방향으로 계속 탐색
        while (true)
        {
            int ny = y + dir[i][0] * (dist + 1);
            int nx = x + dir[i][1] * (dist + 1);

            // 범위 벗어나면 종료
            if (ny < 0 || nx < 0 || ny >= 8 || nx >= 8)
                break;

            if (board[ny][nx] == opposite)
            {
                dist++; // 반대 색의 돌을 만났으면 탐색을 계속
            }
            else if (board[ny][nx] == curColor)
            {
                // 같은 색을 만난 경우
                canFlip = true;
                break;
            }
            else
            {
                // 빈칸을 만나면 뒤집을 수 없음
                break;
            }
        }

        // 뒤집을 수 있으면 색을 변경
        if (canFlip)
        {
            changeColor(y, x, i, dist); // 해당 방향으로 색을 변경
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int N;
    cin >> N;

    // 플레이된 각 돌의 좌표를 처리
    for (int i = 1; i <= N; i++)
    {
        int x, y;
        cin >> x >> y;
        // 좌표를 0-based로 변경
        place(i, y, x);
    }

    // 결과 출력
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == 0)
                cout << '_';
            else if (board[i][j] == 1)
                cout << '@';
            else
                cout << 'O';
        }
        cout << '\n';
    }

    return 0;
}
