// modified dijkstra i assume
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

struct pipe
{
    // int sy, sx;
    int dy, dx;
    int cost;
};

struct Edge
{
    int y, x;
    int cost;

    bool operator<(Edge right) const
    {
        if (cost < right.cost)
            return false;
        if (cost > right.cost)
            return true;
        return false;
    }
};

int N, M;
int field[31][31] = {
    0,
};
vector<pipe> tunnel[31][31];
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int dist[31][31];

int dijkstra(int starty, int startx)
{
    priority_queue<Edge> pq;
    pq.push({starty, startx, 0});
    dist[starty][startx] = 0;

    while (!pq.empty())
    {
        Edge now = pq.top();
        pq.pop();

        // you arrived at your destination
        if (now.y == N && now.x == N)
        {
            return now.cost;
        }

        if (dist[now.y][now.x] < now.cost)
            continue;

        int sz = tunnel[now.y][now.x].size();

        // if there exists pipes from current now Edge
        if (sz > 0)
        {
            for (int i = 0; i < sz; i++)
            {
                pipe cur = tunnel[now.y][now.x][i];

                // inequality resulted into excessive time complexity
                if (dist[cur.dy][cur.dx] <= now.cost + cur.cost)
                    continue;

                dist[cur.dy][cur.dx] = now.cost + cur.cost;
                pq.push({cur.dy, cur.dx, now.cost + cur.cost});
            }
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dir[i][0];
            int nx = now.x + dir[i][1];

            if (ny < 1 || nx < 1 || ny > N || nx > N)
                continue;

            int nextcost;

            // the road is ascending
            if (field[ny][nx] > field[now.y][now.x])
            {
                int diff = field[ny][nx] - field[now.y][now.x];

                nextcost = now.cost + (diff * 2);
            }
            // when the road is flat
            else if (field[ny][nx] == field[now.y][now.x])
            {
                nextcost = now.cost + 1;
            }
            else // when the road is descending
            {
                nextcost = now.cost;
            }

            if (dist[ny][nx] > nextcost)
            {
                dist[ny][nx] = nextcost;
                pq.push({ny, nx, nextcost});
            }
        }
    }
    return -1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        memset(field, 0, sizeof(field));
        /**
         * does work correctly if you want to initialize all elements in field to zero.
         * This is because memset can reliably set memory to 0 since zero has the same
         * byte representation (0x00) across all types.
         *
         * When to Use memset with Caution
         * Non-zero Values: memset only works reliably for zero initialization (0),
         * not for other values like INT_MAX or -1.
         * Complex Data Types: Avoid using memset with types that have complex or non-trivial
         * constructors, like std::vector, as it can cause undefined behavior.
         */
        // i cannot use clear() on 2d vector.
        // tunnel.clear();
        // memset(dist, INT_MAX, sizeof(dist));
        /**
         * does not correctly set all elements of dist to INT_MAX.
         * This is because memset works at the byte level and can only set memory
         * to a specific byte value, not an integer value.
         * INT_MAX is typically larger than a single byte, so memset will not produce
         * the expected result.
         */
        // fill(dist.begin(), dist.end(), INT_MAX);

        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 31; j++)
            {
                tunnel[i][j].clear();
                dist[i][j] = INT_MAX;
            }
        }

        cin >> N >> M;

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                cin >> field[i][j];
            }
        }

        while (M--)
        {
            int sy, sx, dy, dx, c;
            cin >> sy >> sx >> dy >> dx >> c;

            tunnel[sy][sx].push_back({dy, dx, c});
            tunnel[dy][dx].push_back({sy, sx, c});
        }

        int answer = dijkstra(1, 1);

        cout << "#" << tc << " " << answer << '\n';
    }
}
