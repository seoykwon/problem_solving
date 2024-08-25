#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int cheese[21][21]; // 시골쥐에서 치즈까지의 거리
int city[21][21];   // 치즈에서 도시쥐까지의 거리
char board[21][21]; // 집의 정보
int N, M;
int sy, sx; // 시골쥐의 초기 위치

struct Node
{
    int y;
    int x;
};

Node cheeseNode, cityNode; // 치즈와 도시쥐 위치

int bfs(int y, int x, int arr[21][21], Node target)
{
    queue<Node> q;
    q.push({y, x});
    arr[y][x] = 0; // 시작 지점의 거리 초기화

    int ydir[] = {-1, 0, 1, 0};
    int xdir[] = {0, -1, 0, 1};

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        // 도착 지점에 도달했을 때
        if (now.y == target.y && now.x == target.x)
        {
            return arr[now.y][now.x];
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            // 범위를 벗어나거나 벽이면 무시
            if (ny < 0 || nx < 0 || ny >= N || nx >= M || board[ny][nx] == 'x')
                continue;

            // 아직 방문하지 않은 칸만 큐에 추가
            if (arr[ny][nx] == -1)
            {
                arr[ny][nx] = arr[now.y][now.x] + 1;
                q.push({ny, nx});
            }
        }
    }
    return -1; // 도달할 수 없을 경우
}

int main()
{
    memset(cheese, -1, sizeof(cheese)); // -1로 초기화해서 방문 여부 확인
    memset(city, -1, sizeof(city));     // -1로 초기화해서 방문 여부 확인

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> board[i][j];

            if (board[i][j] == 'S')
            {
                sy = i;
                sx = j;
                board[i][j] = '.';
            }
            else if (board[i][j] == 'C')
            {
                cheeseNode = {i, j};
            }
            else if (board[i][j] == 'D')
            {
                cityNode = {i, j};
            }
        }
    }

    int r1 = bfs(sy, sx, cheese, cheeseNode);                 // 시골쥐에서 치즈까지 최단 거리
    int r2 = bfs(cheeseNode.y, cheeseNode.x, city, cityNode); // 치즈에서 도시쥐까지 최단 거리

    cout << r1 + r2 << endl; // 총 이동 시간 출력
    return 0;
}
