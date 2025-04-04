#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#define INT_MAX 0x7fffffff

using namespace std;

int binSearch(vector<int> &arr, int value)
{
    int ans = arr.size();
    int L = 0, R = int(arr.size()) - 1, mid = 0;

    while (L <= R)
    {
        mid = (L + R) / 2;
        if (arr[mid] >= value)
        { // value 이상인 위치를 보고 있다면
            ans = mid;
            R = mid - 1;
        }
        else
        { // value 미만인 위치를 보고 있다면
            L = mid + 1;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++)
    {
        int N, M, c1, c2;
        cin >> N >> M;
        cin >> c1 >> c2;
        int dx = abs(c1 - c2);

        vector<int> cows(N);
        for (int i = 0; i < N; i++)
        {
            cin >> cows[i];
        }
        sort(cows.begin(), cows.end());

        int minDist = INT_MAX;
        int count = 0;

        for (int i = 0; i < M; i++)
        {
            int hPos;
            cin >> hPos;

            int X = binSearch(cows, hPos); // X := hPos 이상인 소들 중에서 제일 왼쪽 소

            // 1. hPos 와 cows[X] 사이의 거리
            if (X < cows.size())
            { // hPos 오른쪽에 소가 "존재" 한다면, 그 소와의 거리 갱신
                int dist = cows[X] - hPos;
                if (minDist == dist)
                { // 알고 있던 최소 거리랑 같다면, 경우의 수 증가시키기
                    count++;
                }
                else if (minDist > dist)
                {                   // 알고있던 최소 거리보다 더 좋다면,
                    minDist = dist; // 해당 값으로 갱신
                    count = 1;      // 1번 있다.
                }
            }

            // 2. hPos 와 cows[X - 1] 사이의 거리
            if (X - 1 >= 0)
            { // hPos 왼쪽에 소가 "존재" 한다면, 그 소와의 거리 갱신
                int dist = hPos - cows[X - 1];
                if (minDist == dist)
                { // 알고 있던 최소 거리랑 같다면, 경우의 수 증가시키기
                    count++;
                }
                else if (minDist > dist)
                {                   // 알고있던 최소 거리보다 더 좋다면,
                    minDist = dist; // 해당 값으로 갱신
                    count = 1;      // 1번 있다.
                }
            }
        }

        cout << "#" << test_case << " " << (dx + minDist) << " " << count << "\n";
    }
}
