#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Time
{
    int s;
    int e;
    Time() {}
    Time(int s, int e) : s(s), e(e) {}
};

vector<Time> arr;
vector<int> sum;
int N;

int upperBound(int target)
{
    int start = 0;
    int end = N - 1;
    int answer = N;

    while (start <= end)
    {
        int mid = (start + end) / 2;

        if (arr[mid].e > target)
        {
            answer = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return answer;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++)
    {
        int L;
        cin >> L;
        int result = -1;
        cin >> N;

        arr.clear();
        sum.clear();
        arr.resize(N);
        sum.resize(N);

        for (int i = 0; i < N; i++)
        {
            int s, e;
            cin >> s >> e;
            arr[i] = Time(s, e);

            if (i == 0)
            {
                sum[i] = e - s;
            }
            else
            {
                sum[i] = sum[i - 1] + (e - s);
            }
        }

        for (int i = 0; i < N; i++)
        {
            int target = arr[i].s + L;
            int ub = upperBound(target);
            int temp = sum[ub - 1];

            if (i != 0)
            {
                temp -= sum[i - 1];
            }
            if (ub != N && target > arr[ub].s)
            {
                temp += (target - arr[ub].s);
            }
            result = max(result, temp);
        }
        cout << "#" << test_case << " " << result << "\n";
    }
    return 0;
}