#include <iostream>
#include <queue>

using namespace std;

int n;
int arr[501][501];

struct path
{
    char from;
    char to;
    int weight;
};

struct cmp
{
    bool operator()(path a, path b)
    {
        // return a.weight > b.weight; // 작은 애가 먼저
        if (a.weight > b.weight)
            return true;
        if (a.weight < b.weight)
            return false;

        if (a.from > b.from)
            return true;
        if (a.from < b.from)
            return false;

        if (a.to > b.to)
            return true;
        if (a.to < b.to)
            return false;

        return true;
    }
};

priority_queue<path, vector<path>, cmp> pq;

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
            int w = arr[i][j];
            path p = {i, j, w};
            if (j > i && w > 0)
            {
                pq.push(p);
            }
        }
    }

    int round = 10;
    path now;
    while (round--)
    {
        now = pq.top();
        pq.pop();

        int nw = now.weight * 2;

        path tmp = {now.from, now.to, nw};
        now = tmp;
        pq.push(now);
    }

    cout << now.weight << "만원";
}