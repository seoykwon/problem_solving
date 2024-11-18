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