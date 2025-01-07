#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        int n, k, w;
        cin >> n >> k; // 건물의 개수 n, 건설 순서 규칙의 개수 k

        vector<int> time(n + 1);         // 각 건물을 짓는 데 걸리는 시간간
        vector<int> dp(n + 1);           // 각 건물을 완성하는데 걸리는 최소 시간간
        vector<int> in_degree(n + 1, 0); // 각 건물의 진입 차수수
        vector<vector<int>> adj(n + 1);  // 건설 순서를 나타내는 그래프

        // 건설 시간 입력
        for (int i = 1; i <= n; i++)
        {
            cin >> time[i];
        }

        // 건설 순서 입력
        for (int i = 0; i < k; i++)
        {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b); // a가 끝나야 b를 시작할 수 있음
            in_degree[b]++;      // b의 진입 차수 증가
        }

        cin >> w;

        queue<int> q;

        // 진입 차수가 0인 건물부터 큐에 넣기
        for (int i = 1; i <= n; i++)
        {
            if (in_degree[i] == 0)
            {
                q.push(i);
                dp[i] = time[i]; // 초기에는 건물 자체의 시간만큼 걸린다다
            }
        }

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            // 현재 건물을 다 지은 후, 그 건물을 선행으로 하는 건물들 처리
            for (int next : adj[cur])
            {
                // 건물을 짓는 데 걸리는 최소 시간 갱신
                dp[next] = max(dp[next], dp[cur] + time[next]);

                // 건설 순서가 끝났으므로 진입 차수를 하나 줄임
                in_degree[next]--;

                // 만약 더 이상 선행 건물이 없다면 큐에 추가
                if (in_degree[next] == 0)
                {
                    q.push(next);
                }
            }
        }

        // 목표 건물 w 완성하는 데 걸리는 시간
        cout << dp[w] << '\n';
    }
}