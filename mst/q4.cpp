#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int T;
int X, Y;
int sx, sy, snum;

char board[51][51];

struct Node
{
    int y;
    int x;
    int num;
};

struct Edge
{
    int from;
    int to;
    int cost;
};

vector<Node> nodes;
vector<Edge> edges;
int parent[2601];
int visited[51][51] = {
    0,
};

bool cmp(Edge a, Edge b)
{
    if (a.cost < b.cost)
        return true;
    if (a.cost > b.cost)
        return false;
    return false;
}

// int valid(Node a, Node b)
// {
//     for (int i = 0; i < Y; i++)
//     {
//         for (int j = 0; j < X; j++)
//         {
//             visited[i][j] = 0;
//         }
//     }
//     // visited 초기화 시켜줘야 함!

//     queue<Node> q;
//     q.push({a.y, a.x, 0});
//     visited[a.y][a.x] = 1;

//     while (!q.empty())
//     {
//         Node now = q.front();
//         q.pop();

//         if (now.y == b.y && now.x == b.x)
//             return now.num;

//         int ydir[4] = {-1, 0, 1, 0};
//         int xdir[4] = {0, -1, 0, 1};

//         for (int i = 0; i < 4; i++)
//         {
//             // 세상에 이러니까 bfs가 제대로 안 돌지!!!
//             // int ny = a.y + ydir[i];
//             // int nx = a.x + xdir[i];
//             int ny = now.y + ydir[i];
//             int nx = now.x + xdir[i];

//             if (ny < 0 || nx < 0 || ny >= Y || nx >= X)
//                 continue;

//             if (board[ny][nx] == '#' || visited[ny][nx])
//                 continue;

//             visited[ny][nx] = 1;
//             q.push({ny, nx, now.num + 1});
//         }
//     }
//     return -1;
// }

void bfs(Node start)
{
    queue<Node> q;
    q.push({start.y, start.x, 0});

    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            visited[i][j] = 0;
        }
    }
    visited[start.y][start.x] = 1;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        if (board[now.y][now.x] == 'A' || board[now.y][now.x] == 'S')
        {
            edges.push_back({
                start.num,
            })
        }
    }
}

void input()
{
    cin >> X >> Y;

    nodes.clear();
    edges.clear();

    int cnt = 0;

    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            cin >> board[i][j];
            visited[i][j] = 0;

            if (board[i][j] == 'S')
            {
                sy = i;
                sx = j;
                snum = cnt;
                nodes.push_back({i, j, cnt});
                cnt++;
            }

            if (board[i][j] == 'A')
            {
                nodes.push_back({i, j, cnt});
                cnt++;
            }
        }
    }

    // if you start j from 0, time limit occurs
    // you need to cut off redundant calculation
    // or use memoization

    // for (int i = 0; i < nodes.size(); i++)
    // {
    //     for (int j = i + 1; j < nodes.size(); j++)
    //     {
    //         if (i == j)
    //             continue;

    //         Node a = nodes[i];
    //         Node b = nodes[j];

    //         // check if there are walls
    //         int validPath = valid(a, b);
    //         if (validPath == -1)
    //             continue;

    //         int dist = validPath; // abs(a.y - b.y) + abs(a.x - b.x);

    //         edges.push_back({a.num, b.num, dist});
    //         // edges.push_back({b.num, a.num, dist});
    //         // 크루스칼은 undirected graph여서 양방향으로 넣어줄 필요가 없어!
    //         // prim은 directed graph여서 넣어줘야 해
    //     }

    //     parent[i] = i;
    // }

    for (int i = 0; i < nodes.size(); i++)
    {
        bfs(nodes[i]);
        parent[i] = i;
    }
}

int Find(int node)
{
    if (node == parent[node])
        return node;

    return parent[node] = Find(parent[node]);
}

void Union(int a, int b)
{
    int rootA = Find(a);
    int rootB = Find(b);

    if (rootA == rootB)
        return;

    parent[rootB] = rootA;
}

int kruskal()
{
    sort(edges.begin(), edges.end(), cmp);
    int totalcost = 0;

    for (int i = 0; i < edges.size(); i++)
    {
        Edge now = edges[i];

        if (Find(now.from) == Find(now.to))
            continue;

        totalcost += now.cost;

        Union(now.from, now.to);
    }
    return totalcost;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> T;

    for (int i = 1; i <= T; i++)
    {
        input();

        cout << kruskal() << endl;
    }
}