#include <iostream>
#include <queue>

using namespace std;

int N;
int a, t;
int maxn = 0;

struct node
{
    int num;
    int a;
    int t;
};

struct cmp
{
    bool operator()(node &left, node &right)
    {
        return left.a > right.a;
    }
};

struct cmp2
{
    bool operator()(node &left, node &right)
    {
        return left.num > right.num;
    }
};

priority_queue<node, vector<node>, cmp> pq;

priority_queue<node, vector<node>, cmp2> pq2;

int limit = 0;

void calculate()
{
    while (!pq.empty())
    {
        auto now = pq.top();
        pq.pop();

        limit = now.a + now.t;

        while (!pq.empty() && pq.top().a <= limit)
        // while (pq.top().a <= limit)
        {
            pq2.push(pq.top());
            pq.pop();
        }

        while (!pq2.empty())
        {
            auto now2 = pq2.top();
            pq2.pop();
            if (maxn < limit - now2.a)
            {
                maxn = limit - now2.a;
            }
            limit = limit + now2.t;
            while (!pq.empty() && pq.top().a <= limit)
            // while (pq.top().a <= limit)
            {
                pq2.push(pq.top());
                pq.pop();
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        cin >> a >> t;
        pq.push({i, a, t});
    }
    calculate();

    cout << maxn << endl;
}

// problems I encountered:
/*
condition with pq.top() without checking if pq is empty:
if the condition pq.top().a <= limit is not satisfied, but the queue is empty,
this will result in calling pq.top() on an empty queue,
leading to undefined behavior or a crash.

However, if the priority queue isn't empty but contains elements that don't satisfy
pq.top().a <= limit, it could create an infinite loop where the condition is never met,
and the loop doesn't teminate.
*/

// ############# 강사님 코드 ##################
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Person
{
    int id;
    int arriveTime;
    int eatTime;
    bool operator<(Person o) const
    {
        if (id < o.id)
            return false;
        if (id > o.id)
            return true;
        return false;
    }
};

bool cmp(Person a, Person b)
{
    if (a.arriveTime < b.arriveTime)
        return true;
    if (a.arriveTime > b.arriveTime)
        return false;
    if (a.id < b.id)
        return true;
    if (a.id > b.id)
        return false;
    if (a.eatTime < b.eatTime)
        return true;
    if (a.eatTime > b.eatTime)
        return false;
    return false;
}

int main()
{
    int N;
    cin >> N;

    vector<Person> v;

    for (int i = 0; i < N; i++)
    {
        int at, et;
        cin >> at >> et;
        v.push_back({i, at, et});
    }

    sort(v.begin(), v.end(), cmp);
    priority_queue<Person> pq;

    int curTime = v[0].arriveTime;
    pq.push(v[0]);
    int idx = 1;
    int res = 0;

    while (!pq.empty() && idx < v.size())
    {
        Person now = pq.top();
        pq.pop();
        res = max(res, curTime - now.arriveTime);
        curTime += now.eatTime;

        while (v[idx].arriveTime <= curTime)
        {
            pq.push(v[idx]);
            idx++;
            if (idx == v.size())
                break;
        }

        if (pq.empty())
        {
            pq.push(v[idx]);
            curTime = v[idx].arriveTime;
            idx++;
        }
    }
    cout << res;
}