// resolve this
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> adj[31]; // 트리의 인접 리스트
int dp[31][2];       // dp[u][0] -> u가 얼리 아답터가 아닐 때, dp[u][1] -> u가 얼리 아답터일 때

void dfs(int node, int parent)
{
    dp[node][0] = 0; // u가 얼리 아답터가 아닐 때는 초기값 0
    dp[node][1] = 1; // u가 얼리 아답터일 때는 최소 1명 (자기 자신)

    for (int next : adj[node])
    {
        if (next == parent)
            continue; // 부모 노드는 다시 방문하지 않음

        // 자식 노드에서 재귀적으로 DFS
        dfs(next, node);

        // u가 얼리 아답터가 아닌 경우, 자식은 반드시 얼리 아답터여야 함
        dp[node][0] += dp[next][1];

        // u가 얼리 아답터일 경우, 자식은 얼리 아답터일 수도 있고 아닐 수도 있음
        dp[node][1] += min(dp[next][0], dp[next][1]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);

    cin >> N;

    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 트리의 임의의 루트에서 DFS 시작 (1번 노드가 루트일 수 있음)
    dfs(1, -1);

    // 루트(1번 노드)에서 얼리 아답터로 최소한 필요한 수를 구함
    cout << min(dp[1][0], dp[1][1]) << endl;

    return 0;
}
