#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, p;
vector<int> a;

int solve()
{
    int ans = 0; // 내가 찾은 최장 스트릭 길이
    for (int i = 0; i < n; i++)
    { // i := 공부를 시작한 날짜의 인덱스
        // a[i] 에 공부를 시작한 상태

        int L = i, R = n - 1, mid;
        while (L <= R)
        {
            mid = (L + R) / 2;
            int blank = (a[mid] - a[i] + 1) - (mid - i + 1); // 빈 날짜 개수
            // a[mid] - a[i] + 1: 실제 날짜 범위 (ex. 3~7이면 5일)
            // mid - i + 1: 실제 공부한 날 수 (배열 내 존재하는 원소 개수)

            if (blank > p)
            { // 불가능
                R = mid - 1;
            }
            else
            { // 가능
                L = mid + 1;
                ans = max(ans, (a[mid] - a[i] + 1) + (p - blank));
            }
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int maximum_date = 1000001;
    int T;
    cin >> T; // 테스트케이스

    for (int test_case = 1; test_case <= T; test_case++)
    {
        cin >> n; // 공부를 한 날
        cin >> p; // 해킹을 할 수 있는 기회

        a.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        int ans = solve();
        cout << "#" << test_case << " " << ans << "\n";
    }

    return 0;
}
