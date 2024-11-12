#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int to;
    int cost;
};

int N, r1, r2;
vector<Edge> path[100000];

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> N >> r1 >> r2;

    for (int i = 0; i < N - 1; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;

        path[from].push_back({to, cost});
        path[to].push_back({from, cost});
    }
}