#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define MAXV 987654321
using namespace std;

int N, Q;

struct E
{
    int x, y, j, v;
};
struct Node
{
    int d, x, y, j;
    bool operator<(const Node a) const
    {
        return d > a.d;
    }
};
char Map[50][51];
vector<E> G[50][50][6];
priority_queue<Node> pq;

int node_distance(int a, int b)
{
    int result = 0;
    for (int i = a + 1; i <= b; i++)
        result += i * i;
    return result;
}

void connect(int x, int y)
{
    for (int i = 1; i <= 5; i++)
    {
        int result = 0;
        for (int j = i + 1; j <= 5; j++)
        {
            result += j * j;
            G[x][y][i].push_back({x, y, j, result});
        }
    }
    for (int i = 1; i <= 5; i++)
    {
        for (int j = i - 1; j >= 1; j--)
        {
            G[x][y][i].push_back({x, y, j, 1});
        }
    }

    for (int i = 1; i <= 5; i++)
    {
        if (x + i >= N)
            break;
        if (Map[x + i][y] == '#')
            break;
        if (Map[x + i][y] == 'S')
            continue;
        G[x][y][i].push_back({x + i, y, i, 1});
    }
    for (int i = 1; i <= 5; i++)
    {
        if (x - i < 0)
            break;
        if (Map[x - i][y] == '#')
            break;
        if (Map[x - i][y] == 'S')
            continue;
        G[x][y][i].push_back({x - i, y, i, 1});
    }
    for (int i = 1; i <= 5; i++)
    {
        if (y + i >= N)
            break;
        if (Map[x][y + i] == '#')
            break;
        if (Map[x][y + i] == 'S')
            continue;
        G[x][y][i].push_back({x, y + i, i, 1});
    }
    for (int i = 1; i <= 5; i++)
    {
        if (y - i < 0)
            break;
        if (Map[x][y - i] == '#')
            break;
        if (Map[x][y - i] == 'S')
            continue;
        G[x][y][i].push_back({x, y - i, i, 1});
    }
}
void make_graph()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Map[i][j] == '.')
                connect(i, j);
        }
    }
}
int solution(int a, int b, int c, int d)
{
    bool visited[50][50][6] = {false};
    while (!pq.empty())
        pq.pop();
    int dist[50][50][6];
    int result = MAXV;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 1; k < 6; k++)
                dist[i][j][k] = MAXV;
    dist[a][b][1] = 0;
    pq.push({dist[a][b][1], a, b, 1});
    while (!pq.empty())
    {
        Node now = pq.top();
        pq.pop();
        if (now.x == c && now.y == d)
            result = min(result, now.d);
        if (visited[now.x][now.y][now.j])
            continue;
        visited[now.x][now.y][now.j] = true;
        for (auto &i : G[now.x][now.y][now.j])
        {
            if (dist[i.x][i.y][i.j] > dist[now.x][now.y][now.j] + i.v)
            {
                dist[i.x][i.y][i.j] = dist[now.x][now.y][now.j] + i.v;
                pq.push({dist[i.x][i.y][i.j], i.x, i.y, i.j});
            }
        }
    }
    if (result == MAXV)
        return -1;
    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> Map[i];
    }
    make_graph();
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        int result = solution(r1 - 1, c1 - 1, r2 - 1, c2 - 1);
        cout << result << '\n';
    }
    return 0;
}

// ##########################################################
#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>
using namespace std;

#define N 52
int dist[N][N][6], row[N][N], col[N][N], dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
char board[N][N];
int solution(int n)
{
    int startX, startY, endX, endY;
    cin >> startX >> startY >> endX >> endY;
    memset(dist, 0x37, sizeof(dist));
    priority_queue<tuple<int, int, int, int>> q;
    dist[startX][startY][1] = 0;
    q.push(make_tuple(0, startX, startY, 1));
    while (!q.empty())
    {
        int cost = -get<0>(q.top());
        int cx = get<1>(q.top());
        int cy = get<2>(q.top());
        int state = get<3>(q.top());
        q.pop();
        if (cost > dist[cx][cy][state])
            continue;
        if (cx == endX && cy == endY)
            return cost;

        if (state + 1 <= 5 && dist[cx][cy][state + 1] > cost + (state + 1) * (state + 1))
        {
            dist[cx][cy][state + 1] = cost + (state + 1) * (state + 1);
            q.push(make_tuple(-dist[cx][cy][state + 1], cx, cy, state + 1));
        }
        for (int j = state - 1; j >= 1; j--)
            if (dist[cx][cy][j] > cost + 1)
            {
                dist[cx][cy][j] = cost + 1;
                q.push(make_tuple(-cost - 1, cx, cy, j));
            }

        for (int k = 0; k < 4; k++)
        {
            int nx = cx + dx[k] * state;
            int ny = cy + dy[k] * state;
            if (1 <= nx && nx <= n && 1 <= ny && ny <= n)
                ;
            else
                continue;
            if (board[nx][ny] == 'S')
                continue;

            if (k == 0 && col[cx][cy] - col[nx - 1][ny] > 0)
                continue;
            else if (k == 1 && col[nx][ny] - col[cx - 1][cy] > 0)
                continue;
            else if (k == 2 && row[cx][cy] - row[nx][ny - 1] > 0)
                continue;
            else if (k == 3 && row[nx][ny] - row[cx][cy - 1] > 0)
                continue;

            if (dist[nx][ny][state] > cost + 1)
            {
                dist[nx][ny][state] = cost + 1;
                q.push(make_tuple(-cost - 1, nx, ny, state));
            }
        }
    }
    return -1;
}
int main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == '#')
                row[i][j] = col[i][j] = 1;
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            row[i][j] += row[i][j - 1];
    for (int j = 1; j <= n; j++)
        for (int i = 1; i <= n; i++)
            col[i][j] += col[i - 1][j];
    int q;
    cin >> q;
    while (q--)
        cout << solution(n) << '\n';
    return 0;
}

// #####################################################
#include <iostream>
#include <queue>

#define MAX_MAP 50
#define MAX_COST 1 << 29

#define SAFE 0
#define MONSTER 1
#define WALL 2

using namespace std;

struct node
{
    int energy, r, c;
};

int N;
int map[MAX_MAP][MAX_MAP], cost[6][MAX_MAP][MAX_MAP];
int move_r[4] = {-1, 1, 0, 0}, move_c[4] = {0, 0, -1, 1};

void print_cost()
{
    for (int k = 1; k <= 5; k++)
    {
        cout << "energy :" << k << "\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (cost[k][i][j] != MAX_COST)
                    cout << cost[k][i][j] << "\t";
                else
                    cout << "_\t";
            }
            cout << "\n\n";
        }
        cout << ".....................\n";
    }
    cout << "\n\n";
}

bool out_map(int r, int c)
{
    return (r < 0) || (c < 0) || (r >= N) || (c >= N);
}

void clear_cost()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 1; k <= 5; k++)
            {
                cost[k][i][j] = MAX_COST;
            }
        }
    }
}

void search(int start_r, int start_c)
{
    queue<node> q;

    cost[1][start_r][start_c] = 0;
    q.push(node{1, start_r, start_c});

    while (!q.empty())
    {
        node curr_n = q.front();
        q.pop();

        int curr_e = curr_n.energy, curr_r = curr_n.r, curr_c = curr_n.c;

        if (curr_e < 5)
        {
            if (cost[curr_e + 1][curr_r][curr_c] > cost[curr_e][curr_r][curr_c] + (curr_e + 1) * (curr_e + 1))
            {
                cost[curr_e + 1][curr_r][curr_c] = cost[curr_e][curr_r][curr_c] + (curr_e + 1) * (curr_e + 1);
                q.push(node{curr_e + 1, curr_r, curr_c});
            }
        }

        for (int e = curr_e - 1; e >= 1; e--)
        {
            if (cost[e][curr_r][curr_c] > cost[curr_e][curr_r][curr_c] + 1)
            {
                cost[e][curr_r][curr_c] = cost[curr_e][curr_r][curr_c] + 1;
                q.push(node{e, curr_r, curr_c});
            }
        }

        for (int m = 0; m < 4; m++)
        {
            bool jumpable = true;
            int n_r = curr_r, n_c = curr_c;
            for (int e = 0; e < curr_e; e++)
            {
                n_r += move_r[m];
                n_c += move_c[m];

                if (out_map(n_r, n_c))
                {
                    jumpable = false;
                    break;
                }

                if (map[n_r][n_c] == WALL)
                {
                    jumpable = false;
                    break;
                }
            }

            if (!jumpable)
                continue;

            if (map[n_r][n_c] != SAFE)
                continue;

            if (cost[curr_e][n_r][n_c] > cost[curr_e][curr_r][curr_c] + 1)
            {
                cost[curr_e][n_r][n_c] = cost[curr_e][curr_r][curr_c] + 1;
                q.push(node{curr_e, n_r, n_c});
            }
        }
    }
}

int get_cost(int dst_r, int dst_c)
{
    int min_cost = MAX_COST;
    for (int e = 1; e <= 5; e++)
    {
        if (min_cost > cost[e][dst_r][dst_c])
        {
            min_cost = cost[e][dst_r][dst_c];
        }
    }

    return (min_cost == MAX_COST) ? -1 : min_cost;
}

void init()
{
    char c;

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> c;
            switch (c)
            {
            case '.':
                map[i][j] = SAFE;
                break;
            case 'S':
                map[i][j] = MONSTER;
                break;
            case '#':
                map[i][j] = WALL;
                break;
            }
        }
    }
}

int main()
{
    int k;
    queue<int> res_q;
    init();

    cin >> k;
    while (k--)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        clear_cost();
        search(r1 - 1, c1 - 1);
        res_q.push(get_cost(r2 - 1, c2 - 1));
        // print_cost();
        // cout << "\n\n====================\n\n";
    }

    while (!res_q.empty())
    {
        cout << res_q.front() << "\n";
        res_q.pop();
    }

    return 0;
}
