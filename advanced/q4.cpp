#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using matrix = vector<vector<int>>;
using matrixV = vector<vector<bool>>;

typedef struct pos
{
    int y;
    int x;
} Pos;

int depthSearch(matrix &grid, matrixV &isVisited, const Pos now, const int level, const int value)
{
    if (level == 3)
        return value;

    int result = 0;
    const bool isEven = now.x % 2 == 0;
    const Pos around[6] = {{-1, 0}, {(isEven ? -1 : 0), 1}, {(isEven ? 0 : 1), 1}, {1, 0}, {(isEven ? 0 : 1), -1}, {(isEven ? -1 : 0), -1}};

    for (int attach = 3 - level; attach >= 1; attach--)
    {
        vector<bool> combPicker(6, false);
        vector<int> labels = {0, 1, 2, 3, 4, 5};
        for (int index = 0; index < attach; index++)
            combPicker[combPicker.size() - 1 - index] = true;

        do
        {
            vector<int> finalPicked;
            for (int index = 0; index < 6; index++)
                if (combPicker[index])
                    finalPicked.push_back(labels[index]);

            // 접합 가능한 부분 찾기
            vector<Pos> finalPos;
            for (const auto &index : finalPicked)
            {
                Pos temp = {now.y + around[index].y, now.x + around[index].x};
                if (0 <= temp.y && temp.y < grid.size() && 0 <= temp.x && temp.x < grid[0].size())
                    if (!isVisited[temp.y][temp.x])
                        finalPos.push_back(temp);
            }

            // DFS 준비
            int nextValue = value;
            for (const auto &target : finalPos)
            {
                nextValue += grid[target.y][target.x];
                isVisited[target.y][target.x] = true;
            }

            // DFS 레벨 진입
            for (const auto &target : finalPos)
            {
                result = max(result, depthSearch(grid, isVisited, target,
                                                 level + static_cast<int>(finalPos.size()), nextValue));
            }

            // DFS 정리
            for (const auto &target : finalPos)
                isVisited[target.y][target.x] = false;

        } while (next_permutation(combPicker.begin(), combPicker.end()));
    }

    return result;
}

int main(int argc, char **argv)
{
    int noTest;
    cin >> noTest;

    for (int test = 0; test < noTest; test++)
    {
        int height, width;
        cin >> height >> width;
        matrix honeycomb(height, vector<int>(width, 0));
        for (auto &list : honeycomb)
            for (auto &value : list)
                cin >> value;

        int result = 0;
        matrixV isVisited(height, vector<bool>(width, false));
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                isVisited[row][col] = true;
                result = max(result, depthSearch(honeycomb, isVisited, {row, col},
                                                 0, honeycomb[row][col]));
                isVisited[row][col] = false;
            }
        }

        cout << "#" << test + 1 << " " << result << "\n";
    }
    return 0;
}

// ############################## 경훈님 코드 ##########################################
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int T;
int N, M;
int ans = 0;
int MAP[20][20];
int visited[20][20];
int MAX;

void Input()
{
    cin >> N >> M; // 세로 가로
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];  // 맵 입력
            visited[i][j] = 0; // 방문기록 초기화
        }
    }
    MAX = 0; // tc마다 맥스 초기화
}

int direct1[6][2] = {
    -1, -1,
    -1, 0,
    -1, 1,
    0, -1,
    0, 1,
    1, 0}; // 짝수 열인 경우 아래 대각선 빼고 6방향 이동가능

int direct2[6][2] = {
    -1, 0,
    0, -1,
    0, 1,
    1, -1,
    1, 0,
    1, 1}; // 홀수 열인 경우 위 대각선 빼고 6방향 이동가능

void dfs(int y, int x, int sum, int level)
{
    if (level == 3)
    {
        MAX = max(MAX, sum);
        return;
    }

    for (int i = 0; i < 6; i++)
    {
        int ny = -1, nx = -1;
        if (x % 2 == 0)
        {
            ny = y + direct1[i][0];
            nx = x + direct1[i][1];
        }
        else if (x % 2 == 1)
        {
            ny = y + direct2[i][0];
            nx = x + direct2[i][1];
        }
        if (ny < 0 || nx < 0 || ny >= N || nx >= M)
            continue; // 맵 이탈 시 패스
        if (visited[ny][nx] == 1)
            continue; // 갔던 곳 다시 안감
        visited[ny][nx] = 1;
        dfs(ny, nx, sum + MAP[ny][nx], level + 1);
        visited[ny][nx] = 0;
    }
}

void Solution()
{
    /*
    DFS로 각 지점에서 출발해 3번 이동한 뒤 4칸의 값의 합을 구하면 될듯

    */

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            visited[i][j] = 1;
            dfs(i, j, MAP[i][j], 0); // 위치와 해당 지점의 값을 더해 dfs go
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j < M - 1; j++)
        {
            int triangle = MAP[i][j];
            if (i < N - 1 && j % 2 == 1)
            {
                triangle += MAP[i][j - 1] + MAP[i][j + 1] + MAP[i + 1][j];
            }
            else if (i > 0 && i < N - 1 && j % 2 == 0)
            {
                triangle += MAP[i - 1][j - 1] + MAP[i - 1][j + 1] + MAP[i + 1][j];
            }
            MAX = max(MAX, triangle);

            int revtri = MAP[i][j];
            if (i > 0 && i < N - 1 && j % 2 == 1)
            {
                revtri += MAP[i + 1][j - 1] + MAP[i + 1][j + 1] + MAP[i - 1][j];
            }
            else if (i > 0 && j % 2 == 0)
            {
                revtri += MAP[i][j - 1] + MAP[i][j + 1] + MAP[i - 1][j];
            }
            MAX = max(MAX, revtri);
        }
    }

    ans = MAX;
}

int main()
{
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        Input();
        Solution();
        cout << "#" << tc << " " << ans << endl;
    }

    return 0;
}