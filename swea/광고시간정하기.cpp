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

vector<Time> arr; // arr[i] := i 번 광고의 시작, 끝 정보
vector<int> sum;  // sum[i] := 첫 i 개 광고들의 총 시간
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
            int target = arr[i].s + L;   // i 번 광고 시작부터 L 시간 동안 틀면 (arr[i].s + L) 까지 광고
            int ub = upperBound(target); // target보다 늦게 끝나는 첫 번째 광고 찾기
            int temp = sum[ub - 1];      // 광고가 나가는 시간

            if (i != 0)
            {
                temp -= sum[i - 1];
            }
            if (ub != N && target > arr[ub].s)
            { // 마지막 광고가 나가는 시간 누적
                temp += (target - arr[ub].s);
            }

            result = max(result, temp);
        }

        cout << "#" << test_case << " " << result << "\n";
    }

    return 0;
}
