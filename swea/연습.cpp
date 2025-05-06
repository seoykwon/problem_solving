#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct E
{
    int end, weight;

    E(int end, int weight) : end(end), weight(weight) {}

    bool operator<(const E &other) const
    {
        return weight > other.weight;
    }
};

unordered_map<int, int> id2idx;
vector<vector<E>> fwdList, revList;
int Num;

vector<int> dijkstra(const vector<vector<E>> &fwdList, int mHub)
{
    int X = id2idx[mHub];
    vector<bool> visit(Num, false);
    vector<int> distance(Num, INT_MAX);

    priority_queue<E> pq;
    pq.emplace(X, 0);
    distance[X] = 0;

    while (!pq.empty())
    {
        E curNode = pq.top();
        pq.pop();
        int cur = curNode.end;

        if (visit[cur])
            continue;
        visit[cur] = true;

        for (const E &n : fwdList[cur])
        {
            if (distance[n.end] > distance[cur] + n.weight)
            {
                distance[n.end] = distance[cur] + n.weight;
                pq.emplace(n.end, distance[n.end]);
            }
        }
    }

    return distance;
}

int init(int N, int sCity[], int eCity[], int mCost[])
{
    id2idx.clear();
    int idx = 0;

    return 0;
}

void add(int sCity, int eCity, int mCost)
{
    return;
}

int cost(int mHub)
{
    return 0;
}