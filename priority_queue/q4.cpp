#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct printer
{
    int startTime;
    int lasting;
    int priority;

    // minimum heap
    bool operator<(printer right) const
    {
        if (priority < right.priority)
            return false;
        if (priority > right.priority)
            return true;
        return false;
    }
};

struct node
{
    int priority;
    int startTime;
    int lasting;
};

int N;
int maxWaiting = 0;
vector<node> print;

bool cmp(node a, node b)
{
    if (a.startTime < b.startTime)
        return true;
    if (a.startTime > b.startTime)
        return false;
    return false;
}

int maxLast()
{
    int idx = 0;
    while (idx < N)
    {
        node start = print[idx];
        int end = start.startTime + start.lasting;

        priority_queue<printer> pq;
        for (int i = idx + 1; i < N; i++)
        {
            if (print[i].startTime <= end)
            {
                node tmp = print[i];
                pq.push({tmp.startTime, tmp.lasting, tmp.priority});
            }
            else
            {
                idx = i;
                break;
            }
        }

        while (!pq.empty())
        {
            printer now = pq.top();
            pq.pop();

            maxWaiting = max(maxWaiting, (end - now.startTime));
            end = end + now.lasting;

            if (print[idx].startTime <= end)
            {
                pq.push({print[idx].startTime, print[idx].lasting, print[idx].priority});
                idx++;
            }
        }
    }
    return maxWaiting;
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        int startT, l;
        cin >> startT >> l;

        print.push_back({i, startT, l});
    }
    sort(print.begin(), print.end(), cmp);

    cout << maxLast() << '\n';

    return 0;
}