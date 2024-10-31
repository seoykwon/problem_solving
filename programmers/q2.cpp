#include <string>
#include <vector>

using namespace std;

int visited[201] = {
    0,
};
int cnt = 0;

void dfs(int node, vector<vector<int>> computers)
{
    visited[node] = 1;

    for (int neighbor = 0; neighbor < computers.size(); neighbor++)
    {
        if (computers[node][neighbor] == 1 && !visited[neighbor])
        {
            dfs(neighbor, computers);
        }
    }
}

int solution(int n, vector<vector<int>> computers)
{

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(i, computers);
            cnt++;
        }
    }

    return cnt;
}