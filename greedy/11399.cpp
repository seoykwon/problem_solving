#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    int time[1001] = {
        0,
    };
    for (int i = 0; i < n; i++)
    {
        cin >> time[i];
    }

    sort(time, time + n);

    int greedy[1001] = {
        0,
    };
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            greedy[i] += time[j];
        }
        // cout << "greedy" << i << " : " << greedy[i] << '\n';
    }

    int waiting = 0;

    for (int i = 0; i < n; i++)
    {
        waiting += greedy[i];
    }
    cout << waiting << '\n';
    return 0;

    /**
     * array 초기화 안 해 두면 쓰레기 값이 사용되어서 터무니 없이 큰 값이
     * 정답으로 출력될 수 있음. 자료구조를 알맞은 값으로 초기화 하는 습관을 가져라.
     */
}