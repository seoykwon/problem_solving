#include <iostream>
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int w, h, p, q, t;
    cin >> w >> h >> p >> q >> t;

    // x와 y 좌표를 독립적으로 계산
    int new_x = (p + t) % (2 * w); // 주기적으로 반복
    int new_y = (q + t) % (2 * h);

    // 반사 이동 처리
    if (new_x > w)
        new_x = 2 * w - new_x;
    if (new_y > h)
        new_y = 2 * h - new_y;

    cout << new_x << " " << new_y << '\n';
    return 0;
}

/**
 * 일단 개미는 처음 오른쪽 위 45도 방향으로 움직이기 시작하고
각각의 축에 대한 이동은 각각의 축에 해당하는 벽에 부딪혔을 때 적용되니 독립적으로 볼 수 있죠.
여기서 x, y 좌표를 독립적으로 처리해도 되는거고요.

그리고 결국 가로 w 세로 h인 직사각형 내부에서 이동하는 것이기 때문에, 각각 축에 대한 이동은 2 * w, 2 * h 주기로 반복이 될 거니까
(현재 좌표 + 시간) % 주기 를 하게 되면 각각 축에 해당하는 상태를 계산할 수 있고, ( 줄 10-12)
이를 다시 격자판 위의 상황으로 매핑시키면 답이 됩니다. (줄 14-18)
 */