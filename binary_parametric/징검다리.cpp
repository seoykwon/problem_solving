#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int distance, vector<int> rocks, int n)
{
    int answer = 0;
    sort(rocks.begin(), rocks.end());
    rocks.push_back(distance); // 도착지점을 바위처럼 취급

    int left = 1;
    int right = distance;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        int prev = 0;
        int removed = 0;

        for (int i = 0; i < rocks.size(); ++i)
        {
            if (rocks[i] - prev < mid)
            {
                removed++; // 최소 거리 유지 못하므로 제거
            }
            else
            {
                prev = rocks[i]; // 최소 거리 유지 가능
            }
        }

        if (removed > n)
        {
            right = mid - 1; // 너무 많이 제거했음 → mid 줄여야 함
        }
        else
        {
            answer = mid; // mid 가능 → 더 큰 최소 거리 탐색
            left = mid + 1;
        }
    }

    return answer;
}