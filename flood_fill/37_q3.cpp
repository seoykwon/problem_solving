#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int MAP[4][5];     // 폭죽의 초기 상태를 저장하는 맵
int visited[4][5]; // 각 위치의 방문 여부와 방문 시간을 저장하는 맵
struct Node
{
    int y;
    int x;
};
int maxTime = 0; // 하늘 전체를 불꽃으로 채우는 데 걸리는 시간을 저장

// BFS를 통해 하늘 전체를 불꽃으로 채우는 데 걸리는 시간을 계산
int bfs()
{
    queue<Node> q;

    // 초기 폭죽 위치를 큐에 추가하고, 방문 기록 설정
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (MAP[i][j] == 1)
            {
                q.push({i, j});
                visited[i][j] = 1;
            }
        }
    }

    int ydir[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // 8방향 이동 y
    int xdir[] = {0, -1, -1, -1, 0, 1, 1, 1}; // 8방향 이동 x

    // BFS 탐색 시작
    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 8; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            // 맵 범위를 벗어난 경우 무시
            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 5)
                continue;

            // 이미 방문한 위치는 무시
            if (visited[ny][nx])
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1; // 방문 시간 기록
            maxTime = visited[ny][nx];                   // 최대 시간 업데이트
            q.push({ny, nx});                            // 큐에 추가하여 다음 탐색을 준비
        }
    }

    return maxTime - 1; // 시작 시간을 1로 두었으므로 결과에서 1을 뺌
}

int main()
{
    // 입력 받기
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> MAP[i][j];
        }
    }

    // BFS 탐색을 통해 하늘 전체를 불꽃으로 채우는 시간을 계산
    cout << bfs() << endl;
    return 0;
}

// ################ 강사님 코드 #####################
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int y;
    int x;
    int level;
};
int direct[8][2] = {-1, 0, 1, 0, 0, 1, 0, -1, -1, -1, -1, 1, 1, -1, 1, 1};

int map[4][5];
int used[4][5];

Node q[11000];
int h, t;

int main()
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            cin >> map[y][x];
            if (map[y][x] == 1)
            {
                q[t++] = {y, x, 0};
                used[y][x] = 1;
            }
        }
    }

    while (h != t)
    {
        Node now = q[h++];
        for (int i = 0; i < 8; i++)
        {
            int ny = now.y + direct[i][0];
            int nx = now.x + direct[i][1];

            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 5)
                continue;
            if (map[ny][nx] == 1)
                continue;
            if (used[ny][nx] == 1)
                continue;
            used[ny][nx] = 1;

            q[t++] = {ny, nx, now.level + 1};
        }
    }

    cout << q[t - 1].level;

    return 0;
}