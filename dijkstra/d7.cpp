#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int y, x;
    int cost;
    int num;

    bool operator<(Edge right) const
    {
        if (cost < right.cost)
            return false;
        if (cost > right.cost)
            return true;
        return false;
    }
};

struct position
{
    int y, x;
};

vector<Edge> v[31];
int dist[31][31];
int N, A, B;
int board[31][31];
position nodes[31 * 2];
int dir[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}};

// 0 = ground, 1 = water

int dijkstra(int start, int end)
{
    position s = nodes[start];
    position e = nodes[end];

    priority_queue<Edge> pq;
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> N >> A >> B;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char tmp;
            cin >> tmp;

            board[i][j] = (tmp == '(') ? 0 : 1;

            nodes[(i * 4) + j] = {i, j};
        }
    }

    int maxfuel;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;

            maxfuel = max(maxfuel, dijkstra(i, j));
        }
    }

    cout << maxfuel;

    return 0;
}