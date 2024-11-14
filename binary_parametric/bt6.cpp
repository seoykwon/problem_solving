/**
 * 2024-11-14
 * 최대를 구하는 문제와 최소를 구하는 문제의 파라미터 조정 값은 다르다.
 * 또한 오버플로우를 방지해야 한다.
 * int는 2억까지 담을 수 있다. 0이 9개면 1억
 * long long은 10의 68 승까지 넣을 수 있다.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int64;

vector<int> cookTime;

int64 bs(int64 goal)
{
    int64 left = 1;
    int64 right = cookTime[0] * goal;
    int64 ans = 0;

    while (left <= right)
    {
        int64 mid = (left + right) / 2;
        int64 cnt = 0;

        for (int i = 0; i < cookTime.size(); i++)
        {
            int64 quotient = mid / cookTime[i];
            cnt += quotient;
        }

        if (cnt >= goal)
        {
            ans = mid;
            right = mid - 1;
        }
        else if (cnt < goal)
        {
            left = mid + 1;
        }
    }

    return ans;
}

bool cmp(int64 a, int64 b)
{
    if (a < b)
        return false;
    if (a > b)
        return true;
    return false;
}

int main()
{
    // freopen("input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;

        cookTime.push_back(tmp);
    }

    sort(cookTime.begin(), cookTime.end(), cmp);

    int64 res = bs(M);

    cout << res << '\n';
}