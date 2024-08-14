#include <iostream>
#include <queue>
#include <string>

using namespace std;

/*
# = 벽, 0 = 길
#00000#
#0##00#
#00#00#
#00#00#
#00##0#
#000#0#
#00000#
*/

string map[7];
int visited[10][10]; // index = (row, col) value = 몇 차수만에 방문
struct Node
{
    int y, x;
};

void bfs(int y, int x)
{
    // 0. 방향 배열, visited 배열
    int ydir[] = {-1, 1, 0, 0};
    int xdir[] = {0, 0, -1, 1};
    // 1. 대기열 생성
    queue<Node> q;
    // 2. 시작 노드 삽입
    visited[y][x] = 1; // (y, x) 1차수로 기록
    q.push({y, x});

    // 큐가 비기전까지 반복
    while (!q.empty())
    {
        // 3. 맨 앞에 노드를 확인 및 추출
        Node now = q.front();
        q.pop();

        // 4.상하좌우 인접해 있는 다음 후보들을 탐색
        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i]; // now(y, x) 위치에서 다음 후보 상하좌우로 탐색
            int nx = now.x + xdir[i];

            // 맵 범위를 넘어가는지 체크
            if (ny >= 7 || nx >= 7 || ny < 0 || nx < 0)
                continue;
            // visited 기록이 있다면 무시 = 차수가 기록되어 있다면 무시
            if (visited[ny][nx] != 0)
                continue;

            // 맵 상에서 다음 좌표가 벽이라면 무시
            if (map[ny][nx] == '#')
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1; // now(y,x) + 1 차수 만큼 더 간다
            q.push({ny, nx});
        }
    }
}

int main()
{
    for (int i = 0; i < 7; i++)
    {
        cin >> map[i];
    }

    bfs(0, 0);

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

// 대표적인 문제 유형
/*
1. 섬의 개수는 몇 개?
2. 가장 큰 섬의 크기는 얼마인가?
3. 최단 경로 찾기
4. 블럭 쌓기

*/