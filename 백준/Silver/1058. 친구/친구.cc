#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

char arr[51][51] = {0};
int n;
int ans = 0;

int bfs(int node)
{
    queue<pair<int, int>> q;
    vector<bool> visited(n, false);
    q.push({node, 0});
    visited[node] = true;
    int cnt = 0;

    while (!q.empty())
    {
        int now = q.front().first;
        int depth = q.front().second;
        q.pop();

        for (int next = 0; next < n; next++)
        {
            if (arr[now][next] == 'Y' && !visited[next] && depth + 1 <= 2)
            {
                visited[next] = true;
                q.push({next, depth + 1});
                cnt++;
            }
        }
    }
    return cnt;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        ans = max(ans, bfs(i));
    }
    cout << ans << endl;
    return 0;
}
