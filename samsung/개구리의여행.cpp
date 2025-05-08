#include <iostream>
#include <climits>
#include <queue>

using namespace std;

#define SAFE 0
#define SLIPPERY 1
#define COUSIN 2

#define MAX_N 50

int N;
int rock[MAX_N][MAX_N];
int Q;
int dist[MAX_N][MAX_N][6];
int r1, c1, r2, c2;

struct Edge
{
    int y, x;
    int jenergy;

    bool operator<(const Edge right) const
    {
        return jenergy > right.jenergy;
    }
};

void init()
{
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char c;
            cin >> c;

            switch (c)
            {
            case '.':
                rock[i][j] = SAFE;
                break;
            case 'S':
                rock[i][j] = SLIPPERY;
                break;
            case '#':
                rock[i][j] = COUSIN;
                break;
            }
        }
    }

    cin >> Q;
}

void travel()
{
    fill(&dist[0][0][0], &dist[0][0][0] + sizeof(dist) / sizeof(int), INT_MAX);

    priority_queue<Edge> pq;
    pq.push({r1, c2, 1});
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    init();

    for (int i = 0; i < Q; i++)
    {
        cin >> r1 >> c1 >> r2 >> c2;

        travel();
    }
}