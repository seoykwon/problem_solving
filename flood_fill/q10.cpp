#include <iostream>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int y, x, dist;
};

int T, N, M;
int sy, sx, ty, tx;
int sword_y, sword_x, stick_y, stick_x;
char field[11][11];
int visited[11][11];
int ydir[] = {-1, 1, 0, 0};
int xdir[] = {0, 0, -1, 1};
int hp;

int bfs(int start_y, int start_x, int end_y, int end_x) {
    queue<Node> q;
    // Initialize the visited array to -1
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visited[i][j] = -1;
        }
    }
    
    q.push({start_y, start_x, 0});
    visited[start_y][start_x] = 0;

    while (!q.empty()) {
        Node curr = q.front();
        q.pop();

        if (curr.y == end_y && curr.x == end_x) {
            return curr.dist;
        }

        for (int i = 0; i < 4; i++) {
            int ny = curr.y + ydir[i];
            int nx = curr.x + xdir[i];

            if (ny >= 0 && ny < N && nx >= 0 && nx < M && visited[ny][nx] == -1 && field[ny][nx] != 'x') {
                visited[ny][nx] = curr.dist + 1;
                q.push({ny, nx, curr.dist + 1});
            }
        }
    }

    return INT_MAX; // If the destination cannot be reached
}

int main() {
    // freopen("input.txt", "r", stdin);
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> M;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> field[i][j];
                if (field[i][j] == 'Y') {
                    sy = i;
                    sx = j;
                } else if (field[i][j] == 'M') {
                    ty = i;
                    tx = j;
                } else if (field[i][j] == 'S') {
                    sword_y = i;
                    sword_x = j;
                } else if (field[i][j] == 'T') {
                    stick_y = i;
                    stick_x = j;
                }
            }
        }
        cin >> hp;

        int min_time = INT_MAX;

        // Y -> S -> M path
        int to_sword = bfs(sy, sx, sword_y, sword_x);
        int sword_to_maou = bfs(sword_y, sword_x, ty, tx);
        if (to_sword != INT_MAX && sword_to_maou != INT_MAX) {
            int total_time = to_sword + sword_to_maou + (hp + 4) / 5; // Attack power 5
            min_time = min(min_time, total_time);
        }

        // Y -> T -> M path
        int to_stick = bfs(sy, sx, stick_y, stick_x);
        int stick_to_maou = bfs(stick_y, stick_x, ty, tx);
        if (to_stick != INT_MAX && stick_to_maou != INT_MAX) {
            int total_time = to_stick + stick_to_maou + (hp + 1) / 2; // Attack power 2
            min_time = min(min_time, total_time);
        }

        if (min_time == INT_MAX) {
            cout << "#" << tc << " " << "the world is doomed" << endl;
        } else {
            cout << "#" << tc << " " << min_time << endl;
        }
    }

    return 0;
}

// ####################### 강사님 코드 ###########################
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
    int y, x;
};

int N, M;
string MAP[1000];
int hp;
int yy, yx, ty, tx;
int sy, sx, my, mx;

int bfs(int y, int x) {
    queue<Node> q;
    q.push({y, x});

    int visited[1000][1000];
    memset(visited, 0, sizeof(visited));
    visited[y][x] = 1;

    int ydir[] = {-1, 1, 0, 0};
    int xdir[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;

            if (visited[ny][nx] > 0)
                continue;

            if (MAP[ny][nx] == 'x')
                continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ny, nx});
        }
    }

    if (visited[yy][yx] == 0 || visited[ty][tx] == 0)
        return -1;
    return (visited[yy][yx] - 1) + (visited[ty][tx] - 1);
}

int getTime(int time, int dmg) {
    if (hp % dmg != 0)
        return time + (hp / dmg) + 1;
    else
        return time + (hp / dmg);
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        cin >> N >> M;

        for (int i = 0; i < N; i++) {
            cin >> MAP[i];
            for (int j = 0; j < M; j++) {
                if (MAP[i][j] == 'Y') {
                    yy = i;
                    yx = j;
                }
                if (MAP[i][j] == 'M') {
                    ty = i;
                    tx = j;
                }
                if (MAP[i][j] == 'S') {
                    sy = i;
                    sx = j;
                }
                if (MAP[i][j] == 'T') {
                    my = i;
                    mx = j;
                }
            }
        }

        cin >> hp;
        // 용사 -> 검 -> 마왕 + 마왕을 처치하는데 걸리는 시간
        int swordtime = bfs(sy, sx);
        // 용사 -> 나무막대기 -> 마왕 + 마왕을 처치하는데 걸리는 시간
        int treetime = bfs(my, mx);

        int ans = 0;

        // 용사가 무기를 구할 수 없다면 -> 멸망
        if (swordtime == -1 && treetime == -1) {
            cout << "#" << t << " the world is doomed\n";
            continue;
        }
        // 검만 구할 수 없다면 -> 나무막대기의 시간이 정답
        else if (swordtime == -1) {
            treetime = getTime(treetime, 2);
            ans = treetime;
        }
        // 나무막대기만 구할 수 없다면 -> 검의 시간이 정답
        else if (treetime == -1) {
            swordtime = getTime(swordtime, 5);
            ans = swordtime;
        } else {
            treetime = getTime(treetime, 2);
            swordtime = getTime(swordtime, 5);
            if (swordtime < treetime)
                ans = swordtime;
            else
                ans = treetime;
        }

        cout << "#" << t << " " << ans << "\n";
    }

    return 0;
}