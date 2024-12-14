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
