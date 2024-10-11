#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
int visited[1001];
int arr[10];
int ans;
vector<int> path;
vector<int> LeftChoo;
vector<int> RightChoo;

void dfs(int now)
{
    if (now == N)
    {
        cnt++;
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (visited[i] == 1)
            continue;

        visited[i] = 1;
        path.push_back(arr[i]);

        dfs(now + 1);

        visited[i] = 0;
        path.pop_back();
    }
}

void dfs(int now, int left, int right)
{
    if (now == N)
    {
        cnt++;
        cout << "result(" << cnt << ")";

        for (int i = 0; i < LeftChoo.size(); i++)
        {
            cout << LeftChoo[i] << " ";
        }
        cout << " | ";

        for (int i = 0; i < RightChoo.size(); i++)
        {
            cout << RightChoo[i] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < N; i++)
    {
        if (visited[i] == 1)
            continue;

        // left;
        visited[i] = 1;
        LeftChoo.push_back(arr[i]);
        dfs(now + 1, left + arr[i], right);
        visited[i] = 0;
        LeftChoo.pop_back();

        // right;
        visited[i] = 1;
        RightChoo.push_back(arr[i]);
        dfs(now + 1, left, right + arr[i]);
        RightChoo.pop_back();
        visited[i] = 0;
    }
}

void init()
{
    memset(visited, 0, sizeof(visited));
    ans = 0;
    cnt = 0;
}

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
}

void solution()
{
    dfs(0, 0, 0);
    ans = cnt;
}

int main()
{
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        init();
        input();
        solution();
        cout << "#" << tc << " " << ans << endl;
    }
    return 0;
}