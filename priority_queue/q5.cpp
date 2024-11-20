/**
 * use priority queue (min-heap)
 * to be more specific, start from the boundary of the bowl and gradually expands inside
 *
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int C, R;
vector<vector<int>> grid;     // 그릇의 높이를 나타내는 2D 배열
vector<vector<bool>> visited; // 방문 여부를 체크하는 배열

// 좌 우 상 하
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int water_fill()
{
    // min-heap
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

    // visited initialization
    visited.assign(R, vector<bool>(C, false));

    // 경계의 위치들을 큐에 넣고 방문 처리
    for (int r = 0; r < R; r++)
    {
        for (int c : {0, C - 1})
        {
            pq.push({grid[r][c], {r, c}});
            visited[r][c] = true;
        }
    }
    for (int c = 0; c < C; c++)
    {
        for (int r : {0, R - 1})
        {
            if (!visited[r][c])
            {
                pq.push({grid[r][c], {r, c}});
                visited[r][c] = true;
            }
        }
    }

    int total_water = 0;

    // 우선순위 큐에서 하나씩 꺼내면서 물을 채운다
    while (!pq.empty())
    {
        int height = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        // 4방향으로 확인하여 물을 채울 수 있는지 검사
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 범위를 벗어나지 않는 경우
            if (nx >= 0 && nx < R && ny >= 0 && ny < C && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                // 물이 채워질 수 있는 경우
                if (grid[nx][ny] < height)
                {
                    total_water += height - grid[nx][ny];
                }
                pq.push({max(height, grid[nx][ny]), {nx, ny}});
            }
        }
    }

    return total_water;
}

int main()
{
    cin >> C >> R;
    grid.assign(R, vector<int>(C));
    // assign 함수:
    // It is used to assign the new values to the given number of vector elements
    // by replacing old ones. It also modifies the size of the vector
    // according to the given number of elements.

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> grid[i][j];
        }
    }

    // 결과 출력
    cout << water_fill() << endl;

    return 0;
}

// ############################### 강사님 코드 ################################
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstring>

#define MAX 302

using namespace std;

int N, M;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int ans = 0;

struct Square
{
    int x, y;
    bool operator<(Square i) const
    {
        return map[y][x] > map[i.y][i.x];
    }
};

priority_queue<Square> pq;

void bfs(int x, int y, int h)
{
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[y][x] = true;

    while (!q.empty())
    {
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = curx + dx[i];
            int ny = cury + dy[i];

            if (0 <= nx && nx < M && 0 <= ny && ny < N && !visited[ny][nx])
            {
                visited[ny][nx] = true;

                if (map[ny][nx] > h)
                    pq.push({nx, ny});
                else
                {
                    ans += h - map[ny][nx];
                    q.push({nx, ny});
                }
            }
        }
    }
}

int main()
{
    cin >> M >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];

            if (i == 0 || j == 0 || i == N - 1 || j == M - 1)
            {
                pq.push({j, i});
                visited[i][j] = true;
            }
        }
    }

    while (!pq.empty())
    {
        Square s = pq.top();
        pq.pop();
        bfs(s.x, s.y, map[s.y][s.x]);
    }

    cout << ans;

    return 0;
}

// ############################# 디버깅 용도 ##################################

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int C, R;
vector<vector<int>> grid;     // 그릇의 높이를 나타내는 2D 배열
vector<vector<bool>> visited; // 방문 여부를 체크하는 배열

// 좌 우 상 하
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void print_pq(priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> &pq)
{
    cout << "Priority Queue: ";
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> temp = pq;
    while (!temp.empty())
    {
        cout << "(" << temp.top().first << ", (" << temp.top().second.first << ", " << temp.top().second.second << ")) ";
        temp.pop();
    }
    cout << endl;
}

int water_fill()
{
    // min-heap
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

    // visited 초기화
    visited.assign(R, vector<bool>(C, false));

    // 경계의 위치들을 큐에 넣고 방문 처리
    for (int r = 0; r < R; r++)
    {
        for (int c : {0, C - 1})
        {
            pq.push({grid[r][c], {r, c}});
            visited[r][c] = true;
        }
    }
    for (int c = 0; c < C; c++)
    {
        for (int r : {0, R - 1})
        {
            if (!visited[r][c])
            {
                pq.push({grid[r][c], {r, c}});
                visited[r][c] = true;
            }
        }
    }

    print_pq(pq); // 큐 상태 출력

    int total_water = 0;

    // 우선순위 큐에서 하나씩 꺼내면서 물을 채운다
    while (!pq.empty())
    {
        int height = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        // 큐에서 원소 꺼낼 때마다 출력
        cout << "Popped: (" << height << ", (" << x << ", " << y << "))" << endl;
        print_pq(pq); // 큐 상태 출력

        // 4방향으로 확인하여 물을 채울 수 있는지 검사
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 범위를 벗어나지 않는 경우
            if (nx >= 0 && nx < R && ny >= 0 && ny < C && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                // 물이 채워질 수 있는 경우
                if (grid[nx][ny] < height)
                {
                    total_water += height - grid[nx][ny];
                }
                pq.push({max(height, grid[nx][ny]), {nx, ny}});
            }
        }

        print_pq(pq); // 큐 상태 출력
    }

    return total_water;
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> C >> R;
    grid.assign(R, vector<int>(C));

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> grid[i][j];
        }
    }

    // 결과 출력
    cout << "Total water: " << water_fill() << endl;

    return 0;
}
