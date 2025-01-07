#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2; // 출발점, 도착점

        int n; // 행성계의 개수
        cin >> n;

        int en = 0;
        int dep = 0;

        for (int j = 0; j < n; j++)
        {
            int cx, cy, r;
            cin >> cx >> cy >> r;

            // 출발점을 포함하는 행성계는 이탈, 도착점을 포함하는 행성계는 진입
            if (pow(cx - x1, 2) + pow(cy - y1, 2) <= r * r)
            { // 출발점이 행성계안에있고
                if (pow(cx - x2, 2) + pow(cy - y2, 2) > r * r)
                {          // 도착점이 행성계 밖에 있는경우
                    dep++; // 이탈
                }
            }
            if (pow(cx - x2, 2) + pow(cy - y2, 2) <= r * r)
            { // 도착점이 행성계안에있고
                if (pow(cx - x1, 2) + pow(cy - y1, 2) > r * r)
                {         // 출발점이 행성계 밖에 있는경우
                    en++; // 진입
                }
            }
        }
        cout << en + dep << "\n";
    }
    return 0;
}