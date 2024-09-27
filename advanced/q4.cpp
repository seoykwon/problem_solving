#include <iostream>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
int N, M;
int hive[15][15] = {
    0,
};
bool used[15][15] = {
    false};
int ans = INT_MIN;

int yd_odd[] = {1, 0, -1, 0, -1, -1};
int xd_odd[] = {0, -1, 0, 1, -1, 1};

int yd_even[] = {1, 0, -1, 0, 1, 1};
int xd_even[] = {0, -1, 0, 1, -1, 1};

int tmp_calc = 0;

void dfs(int y, int x, int num)
{
    if (num == 4)
    {
        // cout << tmp_calc << endl;
        ans = max(tmp_calc, ans);
        return;
    }

    int ny = y;
    int nx = x;

    for (int i = 0; i < 6; i++)
    {
        // debugged #1: you need to use nx instead of x
        // you need to use the updated x.
        if (nx % 2 == 0)
        {
            ny = y + yd_even[i];
            nx = x + xd_even[i];
        }
        else
        {
            ny = y + yd_odd[i];
            nx = x + xd_odd[i];
        }

        if (ny < 0 || nx < 0 || ny >= N || nx >= M || used[ny][nx])
            continue;

        used[ny][nx] = true;
        tmp_calc += hive[ny][nx];

        dfs(ny, nx, num + 1);

        used[ny][nx] = false;
        tmp_calc -= hive[ny][nx];
    }
}

// 수리검 모양 체크해 주기
void triangle(int y, int x)
{
    int ydir_odd[] = {0, 1, 0};
    int xdir_odd[] = {-1, 0, 1};

    int ydir_even[] = {-1, 1, 1};
    int xdir_even[] = {0, -1, 1};

    int ny, nx;

    for (int i = 0; i < 3; i++)
    {
        if (x % 2 == 0)
        {
            ny = y + ydir_even[i];
            nx = x + xdir_even[i];
        }
        else
        {
            ny = y + ydir_odd[i];
            nx = x + xdir_odd[i];
        }

        if (ny < 0 || nx < 0 || ny >= N || nx >= M)
            continue;

        tmp_calc += hive[ny][nx];
    }

    ans = max(ans, tmp_calc);
}

int main()
{
    // freopen("input.txt", "r", stdin);

    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        memset(hive, 0, sizeof(hive));
        memset(used, false, sizeof(used));
        // initialize ans
        ans = INT_MIN;
        // ans = 0;

        cin >> N >> M;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cin >> hive[i][j];
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                tmp_calc = hive[i][j];
                used[i][j] = true;
                dfs(i, j, 1);

                triangle(i, j);
                used[i][j] = false;
            }
        }

        cout << "#" << tc << " " << ans << endl;
    }
}

// above code is wrong
// you need to take care of all the possibilites
// like below

//
// Created by IT DICE on 2024-08-06.
//
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