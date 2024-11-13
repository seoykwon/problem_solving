#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> path[31];
int visited[31] = {
    0,
};

void dfs(int node, int mxn)
{
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> N;

    for (int i = 0; i < N - 1; i++)
    {
        int from, to;
        cin >> from >> to;

        path[from].push_back(to);
        path[to].push_back(from);
    }

    int mx = 0;

    dfs(0, mx);

    cout << mx << '\n';
}