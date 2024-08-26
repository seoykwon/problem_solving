#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int pancake[8][8] = {
    0,
};
struct Node
{
    int y;
    int x;
};
Node prawn[64];
Node squid[64];
int p[8][8] = {
    0,
};
int s[8][8] = {
    0,
};
int visitedP[8][8] = {
    0,
};
int visitedS[8][8] = {
    0,
};
int pi, si;
int fail = 0;

void input()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cin >> pancake[i][j];

            if (pancake[i][j] == 1)
            {
                prawn[pi++] = {i, j};
                p[i][j] = 1;
            }

            if (pancake[i][j] == 2)
            {
                squid[si++] = {i, j};
                s[i][j] = 2;
            }
        }
    }
}

void bfs1(int y, int x)
{
    queue<Node> q;
    q.push({y, x});
    visitedP[y][x] = 0;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        int ydir[] = {-1, 0, 1, 0};
        int xdir[] = {0, -1, 0, 1};

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 7 || nx >= 7)
                continue;

            if (visitedP[ny][nx] != -1)
                continue;

            visitedP[ny][nx] = visitedP[now.y][now.x] + 1;
            q.push({ny, nx});

            if (p[ny][nx] == 1)
            {
                if (visitedP[ny][nx] <= 3)
                {
                    cout << "fail";
                    fail = 1;
                    return;
                }
            }
        }
    }
}

void bfs2(int y, int x)
{
    queue<Node> q;
    q.push({y, x});
    visitedS[y][x] = 0;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        int ydir[] = {-1, 0, 1, 0};
        int xdir[] = {0, -1, 0, 1};

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 7 || nx >= 7)
                continue;

            if (visitedS[ny][nx] != -1)
                continue;

            visitedS[ny][nx] = visitedS[now.y][now.x] + 1;
            q.push({ny, nx});

            if (s[ny][nx] == 2)
            {
                if (visitedS[ny][nx] <= 4)
                {
                    cout << "fail";
                    fail = 1;
                    return;
                }
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    input();

    memset(visitedP, -1, sizeof(visitedP));
    memset(visitedS, -1, sizeof(visitedS));

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (pancake[i][j] == 1 && visitedP[i][j] != -1)
            {
                bfs1(i, j);
                if (fail)
                    return 0;
            }

            else if (pancake[i][j] == 2 && visitedS[i][j] != -1)
            {
                bfs2(i, j);
                if (fail)
                    return 0;
            }
        }
    }

    if (!fail)
    {
        cout << "pass";
    }
}

// ######################## 강사님 코드 ###########################
#include <iostream>
#include <queue>
using namespace std;

char MAP[7][8];
struct Node
{
    int y, x;
};
int bfs(int y, int x, char type, int dist)
{
    int visited[7][7] = {0};
    int dy[4] = {-1, 1, 0, 0};
    int dx[4] = {0, 0, -1, 1};
    queue<Node> qu;
    visited[y][x] = 1;
    qu.push({y, x});
    while (!qu.empty())
    {
        Node now = qu.front();
        qu.pop();
        if (visited[now.y][now.x] - 1 >= dist)
            break;
        if (!(now.y == y && now.x == x) && MAP[now.y][now.x] == type)
        {
            return 1;
        }
        for (int t = 0; t < 4; t++)
        {
            int ny = now.y + dy[t];
            int nx = now.x + dx[t];

            if (ny < 0 || nx < 0 || ny >= 7 || nx >= 7)
                continue;
            if (visited[ny][nx] > 0)
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            qu.push({ny, nx});
        }
    }
    return 0;
}

int main()
{
    for (int y = 0; y < 7; y++)
    {
        cin >> MAP[y];
    }
    // '1' 은 새우 '2' 는 오징어
    // 각 해물들의 위치마다 새우면 3칸이상인지 검사, 오징어면 4칸이상인지 검사를 진행한다.
    string ans = "pass";
    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 7; x++)
        {
            if (MAP[y][x] == '1')
            { // 새우
                int ret = bfs(y, x, '1', 3);
                if (ret == 1)
                    ans = "fail";
            }
            if (MAP[y][x] == '2')
            { // 오징어
                int ret = bfs(y, x, '2', 4);
                if (ret == 1)
                    ans = "fail";
            }
        }
    }
    cout << ans;

    return 0;
}