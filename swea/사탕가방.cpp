#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        int N;
        long long M;
        cin >> N >> M;

        vector<long long> candy(N);
        long long max_candy = -1;
        for (int i = 0; i < N; i++)
        {
            cin >> candy[i];
            max_candy = max(max_candy, candy[i]);
        }

        long long low = 1LL;
        long long high = max_candy;
        long long ans = 0;

        while (low <= high)
        {
            long long mid = (low + high) / 2;

            // 가방을 mid 개 만큼 만들 것이라고 결정했다.
            // 각 가방에 최대 몇 개의 사탕을 넣을 수 있는 지
            long long sum = 0LL;
            for (int i = 0; i < N; i++)
            {
                sum += (candy[i] / mid);
            }

            if (sum < M)
            {
                high = mid - 1;
            }
            else
            {
                ans = mid;
                low = mid + 1;
            }
        }

        cout << "#" << tc << " " << ans << "\n";
    }

    return 0;
}
