#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int N; // 한변의 길이
int K; // 최대 공사 가능 깊이
int MAP[10][10];
int visited[10][10];
int cnt;
int ans;
int ydir[] = {-1, 1, 0, 0};
int xdir[] = {0, 0, -1, 1};

struct Node
{
    int y;
    int x;
    int canbreak; // 공사 가능여부
};
vector<Node> v; // 최대 높이를 가지고 있는 봉우리의 좌표

void init()
{
    memset(MAP, 0, sizeof(MAP));
    v.clear();
    ans = 0;
}
void input()
{
    int MAX = -21e8;
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            // 가장 높은 봉우리를 찾고, 관리
            if (MAP[i][j] > MAX)
            { // 9
                MAX = MAP[i][j];
                v.clear();
                v.push_back({i, j, 1});
            }
            else if (MAP[i][j] == MAX)
            { //
                v.push_back({i, j, 1});
            }
        }
    }
}

void dfs(Node now)
{

    if (cnt > ans)
        ans = cnt;
    // 상하좌우 방면으로 내려가면서 진행
    for (int i = 0; i < 4; i++)
    {
        int ny = now.y + ydir[i];
        int nx = now.x + xdir[i];
        if (ny >= N || nx >= N || ny < 0 || nx < 0)
            continue;
        if (visited[ny][nx] == 1)
            continue;

        // 고려해야 할것 now -> next   next의 높이 >= now의 높이
        if (MAP[ny][nx] >= MAP[now.y][now.x])
        {
            if (now.canbreak)
            { // 공사가 가능하다
                // 깎아볼 수 있다.
                for (int d = 1; d <= K; d++)
                { // 7  6
                    // 처리 조건
                    if (MAP[ny][nx] - d >= MAP[now.y][now.x])
                        continue;
                    MAP[ny][nx] -= d;
                    visited[ny][nx] = 1;
                    cnt++; // 등산로의 길이 +1
                    dfs({ny, nx, 0});
                    cnt--;
                    visited[ny][nx] = 0;
                    MAP[ny][nx] += d;
                }
            }
        }
        else
        {
            visited[ny][nx] = 1;
            cnt++; // 등산로의 길이 +1
            dfs({ny, nx, now.canbreak});
            cnt--;
            visited[ny][nx] = 0;
        }
    }
    // 필요시에 깍아본다. K 공사 가능 깊이만큼
}
void solution()
{
    // 9 9 9
    for (int i = 0; i < v.size(); i++)
    {
        cnt = 0;
        memset(visited, 0, sizeof(visited));

        // 초기값 세팅
        Node now = v[i];
        cnt++;
        visited[now.y][now.x] = 1;
        dfs(now);
    }
}
int main()
{

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        init();
        input();
        solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}