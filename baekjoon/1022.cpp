#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

int map[50][5] = {
    0,
};
int r1, c1, r2, c2;

// 소용돌이 만드는 함수
void makeMap()
{

    // 상,좌,하,우
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};

    int offset = 0; // 정사각형 범위 오프셋
    int num = 1;
    int count = 0; // 반복횟수(지금까지 채워진 횟수)
    int x = 0;
    int y = 0;
    while (true)
    {
        // 정사각형 범위 안에 있을때
        if (-offset <= x && x <= offset && -offset <= y && y <= offset)
        {
            // (r1,c1) ~ (r2,c2) 사이에 있을 때
            if (r1 <= x && x <= r2 && c1 <= y && y <= c2)
            {
                map[x - r1][y - c1] = num; // 좌표 이동 후 넣음
                count++;
                if (count == (r2 - r1 + 1) * (c2 - c1 + 1))
                    return; // 개수 다 차면 종료
            }
            num++;
        }
        int k = 0;

        // 상좌하우 세트로 돌림
        while (k < 4)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];
            // 정사각형 범위 안
            if (-offset <= nx && nx <= offset && -offset <= ny && ny <= offset)
            {
                // (r1,c1) ~ (r2,c2) 사이에 있을 때
                if (r1 <= nx && nx <= r2 && c1 <= ny && ny <= c2)
                {
                    map[nx - r1][ny - c1] = num; // 좌표 이동 후 넣음
                    count++;
                    if (count == (r2 - r1 + 1) * (c2 - c1 + 1))
                        return; // 개수 다 차면 종료
                }
                x = nx;
                y = ny;
                num++;
            }
            else
                k++; // 범위 벗어나면 방향 바꿈
        }
        offset++; // 정사각형 크기 키움
        y += 1;   // 다음 진행을 위해 오른쪽 한칸 옮김
    }
}

int findDigit()
{
    int maxNum = -1;
    for (int i = 0; i <= r2 - r1; i++)
    {
        for (int j = 0; j <= c2 - c1; j++)
        {
            maxNum = max(maxNum, map[i][j]);
        }
    }
    return to_string(maxNum).length();
}

void printSolution()
{
    int digit = findDigit();
    for (int i = 0; i <= r2 - r1; i++)
    {
        for (int j = 0; j <= c2 - c1; j++)
        {
            int size = to_string(map[i][j]).length();
            for (int k = 0; k < digit - size; k++)
                cout << " ";
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin >> r1 >> c1 >> r2 >> c2;

    makeMap();
    printSolution();
}