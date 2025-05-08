#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

long long solution(int n, vector<int> times)
{
    long long answer = 0;
    sort(times.begin(), times.end());

    ll left = 1;
    ll right = 1000000000000000000;

    // int mid = left + (right - left) / 2;
    ll mid;

    while (left <= right)
    {
        mid = (left + right) / 2;
        ll sum = 0;
        for (int i = 0; i < times.size(); i++)
        {
            int tmp = times[i];

            sum += (mid / tmp);
        }

        if (sum >= n)
        {
            right = mid - 1;
            answer = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return answer;
}