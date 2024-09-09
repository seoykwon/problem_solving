
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

struct node
{
    int y, x;
};

int N, M;
int field[300][300];
int temp[300][300];
bool visited[300][300];
int ydir[] = {-1, 1, 0, 0};
int xdir[] = {0, 0, -1, 1};

// BFS로 한 덩어리를 탐색
void bfs(int y, int x)
{
    queue<node> q;
    q.push({y, x});
    visited[y][x] = true;

    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;
            if (!visited[ny][nx] && field[ny][nx] > 0)
            {
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }
}

// 빙산이 녹는 처리
void melt()
{
    memcpy(temp, field, sizeof(field));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (field[i][j] > 0)
            {
                int sea_count = 0;
                for (int k = 0; k < 4; k++)
                {
                    int ny = i + ydir[k];
                    int nx = j + xdir[k];
                    if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                        continue;
                    if (field[ny][nx] == 0)
                        sea_count++;
                }
                temp[i][j] -= sea_count;
                if (temp[i][j] < 0)
                    temp[i][j] = 0; // 음수가 되지 않도록
            }
        }
    }

    memcpy(field, temp, sizeof(temp));
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> field[i][j];
        }
    }

    int year = 0;
    while (true)
    {
        memset(visited, false, sizeof(visited));
        int iceberg_count = 0;

        // 빙산 덩어리 탐색
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (field[i][j] > 0 && !visited[i][j])
                {
                    bfs(i, j);
                    iceberg_count++;
                }
            }
        }

        // 덩어리가 2개 이상으로 나뉘면 종료
        if (iceberg_count >= 2)
        {
            cout << year << endl;
            return 0;
        }

        // 빙산이 모두 녹았을 경우 종료
        if (iceberg_count == 0)
        {
            cout << 0 << endl;
            return 0;
        }

        // 빙산 녹이기
        melt();
        year++;
    }

    return 0;
}

// #################################강사님코드###################
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int w, h;
int curMap[302][302];
int nextMap[302][302];
int visit[302][302];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
void dfs(int y, int x)
{
    visit[y][x] = 1;
    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        int ny = y + dx[i];
        int nx = x + dy[i];
        if (!visit[ny][nx] && curMap[ny][nx] > 0)
        {
            dfs(ny, nx);
        }
        if (!visit[ny][nx])
            cnt++;
    }
    curMap[y][x] -= cnt;
}

int main()
{
    scanf("%d %d", &h, &w);
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
            scanf("%d", &curMap[i][j]);
    }
    int year = 0;
    while (1)
    {
        for (int i = 1; i <= h; i++)
        {
            for (int j = 1; j <= w; j++)
                visit[i][j] = 0;
        }
        int check = 0;
        for (int y = 1; y <= h; y++)
            for (int x = 1; x <= w; x++)
                if (curMap[y][x] > 0 && visit[y][x] == false)
                {
                    if (check)
                    {
                        printf("%d", year);
                        return 0;
                    }
                    dfs(y, x);
                    check = 1;
                }
        if (check == 0)
        {
            printf("0");
            return 0;
        }
        year++;
    }
    return 0;
}