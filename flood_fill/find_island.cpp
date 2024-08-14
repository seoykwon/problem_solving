#include <iostream>
#include <queue>

using namespace std;

int H, W;
int MAP[101][101];
int visited[101][101];
int cnt = 0;

struct Node
{
    int y, x;
};

void bfs(int y, int x)
{
    // 0. 방향 배열 + visited 처리
    int ydir[] = {-1, 1, 0, 0};
    int xdir[] = {0, 0, -1, 1};

    // 1. 대기열 준비
    queue<Node> q;

    // 2. 시작 노드 삽입
    visited[y][x] = 1;
    q.push({y, x});

    // 큐가 비기 전까지 반복
    while (!q.empty())
    {
        // 3. 맨 앞에 노드 확인 및 추출 (now)
        Node now = q.front();
        q.pop();

        // 4. now > next 찾기 (다음 후보들을 탐색)
        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            // 판별 or 처리
            if (ny >= H || nx >= W || ny < 0 || nx < 0)
                continue;
            if (visited[ny][nx] == 1)
                continue;
            if (MAP[ny][nx] == 0)
                continue; // the location is ocean

            // 5. 후보들을 대기열에 등록
            visited[ny][nx] = 1;
            q.push({ny, nx});
        }
    }
}

int main()
{
    cin >> H >> W; // 세로 크기, 가로 크기

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> MAP[i][j];
        }
    }

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (MAP[i][j] == 1 && visited[i][j] == 0) // 섬을 발견했는데, 처음 발견한 섬이라면
            {
                bfs(i, j);
                cnt += 1;
            }
        }
    }

    cout << cnt;
}