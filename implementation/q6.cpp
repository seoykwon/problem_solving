#include <iostream>
using namespace std;

int board[20][20];                                       // 바둑판 상태
int direction[4][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}}; // 가로, 세로, 대각선 방향

// 해당 위치에서 특정 방향으로 연속된 바둑알이 5개인지 확인하는 함수
bool checkFive(int y, int x, int color)
{

    for (int d = 0; d < 4; d++)
    {
        int cnt = 1;
        int ny = y + direction[d][0];
        int nx = x + direction[d][1];

        // 해당 방향으로 연속된 바둑알을 셈
        while (ny > 0 && ny <= 19 && nx > 0 && nx <= 19 && board[ny][nx] == color)
        {
            cnt++;
            ny += direction[d][0];
            nx += direction[d][1];
        }

        // // 반대 방향도 확인 (역방향)
        // ny = y - direction[d][0];
        // nx = x - direction[d][1];
        // while (ny > 0 && ny <= 19 && nx > 0 && nx <= 19 && board[ny][nx] == color)
        // {
        //     cnt++;
        //     ny -= direction[d][0];
        //     nx -= direction[d][1];
        // }

        // 정확히 5개의 바둑알이 연결되었는지 확인하고
        // 양 끝에 같은 색의 바둑알이 없는지 확인
        if (cnt == 5)
        {
            // 이전과 다음 위치에 같은 색 바둑알이 있는지 확인
            int prevY = y - direction[d][0];
            int prevX = x - direction[d][1];
            int nextY = y + direction[d][0] * 5;
            int nextX = x + direction[d][1] * 5;

            // 양 끝에 같은 색의 바둑알이 없을 때만 정확히 5개로 인정
            if ((prevY <= 0 || prevY > 19 || prevX <= 0 || prevX > 19 || board[prevY][prevX] != color) &&
                (nextY <= 0 || nextY > 19 || nextX <= 0 || nextX > 19 || board[nextY][nextX] != color))
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // 바둑판 입력
    for (int i = 1; i <= 19; i++)
    {
        for (int j = 1; j <= 19; j++)
        {
            cin >> board[i][j];
        }
    }

    // 바둑판을 순회하며 승부 판단
    for (int i = 1; i <= 19; i++)
    {
        for (int j = 1; j <= 19; j++)
        {
            if (board[i][j] == 1 || board[i][j] == 2)
            {
                int color = board[i][j];
                if (checkFive(i, j, color))
                {
                    cout << color << endl;
                    cout << i << " " << j << endl;
                    return 0;
                }
            }
        }
    }

    // 승부가 나지 않았을 경우
    cout << 0 << endl;
    return 0;
}
