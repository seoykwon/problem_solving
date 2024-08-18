#include <iostream>
#include <queue>
#include <climits>

using namespace std;

int t;
int n;
int field[10][10];
int maxApple;

struct pos{
    int y, x, cntTurn, heading;
};

pos bfs(int startY, int startX, int startHeading, int targetApple) {
    // 방향: 0: 우, 1: 하, 2: 좌, 3: 상
    int ydir[4] = {0, 1, 0, -1};
    int xdir[4] = {1, 0, -1, 0};
    
    queue<pos> q;
    bool visited[10][10][4] = {false};

    q.push({startY, startX, 0, startHeading});
    visited[startY][startX][startHeading] = true;

    while (!q.empty()) {
        pos cur = q.front(); q.pop();
        
        // 다음 사과를 찾았다면 해당 위치와 정보를 반환
        if (field[cur.y][cur.x] == targetApple) {
            return cur;
        }

        // 현재 방향으로 전진
        int ny = cur.y + ydir[cur.heading];
        int nx = cur.x + xdir[cur.heading];

        if (ny >= 0 && nx >= 0 && ny < n && nx < n && !visited[ny][nx][cur.heading]) {
            visited[ny][nx][cur.heading] = true;
            q.push({ny, nx, cur.cntTurn, cur.heading});
        }

        // 오른쪽으로 회전 (현재 heading + 1)
        int newHeading = (cur.heading + 1) % 4;
        if (!visited[cur.y][cur.x][newHeading]) {
            visited[cur.y][cur.x][newHeading] = true;
            q.push({cur.y, cur.x, cur.cntTurn + 1, newHeading});
        }
    }
    return {0, 0, 0, 0}; // 불가능한 경우는 주어지지 않음
}

void input() {
    cin >> n;
    maxApple = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> field[i][j];
            if (field[i][j] > maxApple) {
                maxApple = field[i][j];
            }
        }
    }
}

int main() {
    cin >> t;
    
    for (int order = 1; order <= t; order++) {
        input();

        int totalTurns = 0;
        pos cur_pos = {0, 0, 0, 0}; // 시작 위치는 (0, 0), 방향은 오른쪽(0)

        for (int apple = 1; apple <= maxApple; apple++) {
            cur_pos = bfs(cur_pos.y, cur_pos.x, cur_pos.heading, apple);
            totalTurns += cur_pos.cntTurn;
        }

        cout << "#" << order << " " << totalTurns << endl;
    }
}
