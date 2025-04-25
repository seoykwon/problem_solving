#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <queue>
using namespace std;

int Q, N;
unordered_map<int, int> mp;

struct Edge
{
    int a, b, cost;

    bool operator<(Edge right) const
    {
        if (cost < right.cost)
            return false;
        if (cost > right.cost)
            return true;
        return false;
    }
};

priority_queue<Edge> pq;
int parent[10001];
int total_time = 0;

void construct(int p)
{
    mp.insert({p, N + 1});
    N++;
}

void deconstruct(int q)
{
    mp.erase(q);
    N--;
}

int Find(int node)
{
    if (node == parent[node])
        return node;

    return parent[node] = Find(parent[node]);
}

void Union(int a, int b)
{
    int pa = Find(a);
    int pb = Find(b);

    if (pa == pb)
        return;
    parent[pb] = pa;
}

int scout(int working_ant)
{
    int idx = 0;
    int hnum = 0;
    for (auto house : mp)
    {
        if (idx == 0 && hnum == 0)
        {
            idx = house.second;
            hnum = house.first;
        }
        int idx2 = house.second;
        int hnum2 = house.first;

        if (idx != idx2)
        {
            pq.push({idx, idx2, hnum2 - hnum});
        }

        idx = idx2;
        hnum = hnum2;
    }

    if (working_ant == N)
    {
        return 0;
    }

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();

        if (Find(now.a) == Find(now.b))
            continue;

        Union(now.a, now.b);
        N--;
        total_time += now.cost;

        if (N == working_ant)
        {
            return total_time;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> Q;
    cin.ignore();

    for (int i = 0; i < Q; i++)
    {
        string line;
        getline(cin, line);

        stringstream st(line);

        // char num;
        // st >> num;

        // int cmd = int(num);
        /*
        입력이 안 되고 있는 이유는 switch (cmd)에서 cmd가 int(num)인데,
        여기서 num은 char로 선언되어 있어서 int(num)을 해도 ASCII 값만 가져옵니다.
        예를 들어, '1'의 ASCII 값은 49이기 때문에, cmd == 100 같은 조건은 절대 만족하지 않아요.
        */
        int cmd;
        st >> cmd;

        switch (cmd)
        {
        case 100:
        {
            st >> N;
            for (int i = 1; i <= N; i++)
            {
                int house;
                st >> house;

                mp.insert({house, i});
            }
            break;
        }
        case 200:
        {
            int p;
            st >> p;
            construct(p);
            break;
        }
        case 300:
        {
            int q;
            st >> q;
            deconstruct(q);
            break;
        }
        case 400:
        {
            int r;
            st >> r;
            for (int i = 0; i < 10001; i++)
            {
                parent[i] = i;
            }
            total_time = scout(r);
            cout << total_time << '\n';
            break;
        }
        }
    }
}

// ###############################
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int S[30001];
int G[30001];
bool invalid[30001] = {false};

int N, Q;
int len = 0;
int home[30001];
priority_queue<E> pq;

int bs(int R)
{
    int result = 0;
    int pre = 0;
    int cnt = 0;
    int l = 0;
    int r = 1000000000;

    while (l <= r)
    {
        int mid = (l + r) / 2;
        cnt = 1;
        for (int i = 0; i < len; i++)
        {
            if (!invalid[i])
            {
                pre = home[i];
                break;
            }
        }

        for (int i = 0; i < len; i++)
        {
            if (invalid[i])
                continue;
            if (home[i] - pre > mid)
            {
                cnt++;
                pre = home[i];
            }
        }

        if (cnt <= R)
        {
            result = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return result;
}

int main()
{
    cin >> Q;
    for (int t = 0; t < Q; t++)
    {
        int order;
        cin >> order;
        if (order == 100)
        {
            cin >> N;

            for (int i = 0; i < N; i++)
            {
                int h;
                cin >> h;
                home[len++] = h;
            }
        }
        else if (order == 200)
        {
            int h;
            cin >> h;
            home[len++] = h;
        }
        else if (order == 300)
        {
            int h;
            cin >> h;
            invalid[h - 1] = true;
        }
        else if (order == 400)
        {
            int r;
            cin >> r;
            cout << bs(r) << '\n';
        }
    }
}