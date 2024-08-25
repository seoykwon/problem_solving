// #include <iostream>
// #include <queue>
// #include <cstring>
// using namespace std;

// int hive[4][9];
// // int one[4][9];
// // int two[4][9];
// // int three[4][9];
// // int four[4][9];
// int visited[4][9];
// int oneN, twoN, threeN, fourN;
// struct Node
// {
//     int y;
//     int x;
//     int num;
// };

// void input()
// {
//     memset(visited, 0, sizeof(visited));

//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 9; j++)
//         {
//             cin >> hive[i][j];
//         }
//     }
// }

// int bfs(int y, int x, int num)
// {
//     queue<Node> q;
//     q.push({y, x, num});
//     visited[y][x] = 1;

//     int ans = 0;

//     while (!q.empty())
//     {
//         Node now = q.front();
//         q.pop();

//         int ydir[] = {-1, 0, 1, 0};
//         int xdir[] = {0, -1, 0, 1};

//         for (int i = 0; i < 4; i++)
//         {
//             int ny = now.y + ydir[i];
//             int nx = now.x + xdir[i];

//             if (ny < 0 || nx < 0 || ny >= 4 || nx >= 9 || visited[ny][nx])
//                 continue;

//             if (hive[ny][nx] != num)
//                 continue;

//             visited[ny][nx] = visited[now.y][now.x] + 1;

//             ans = visited[ny][nx];

//             q.push({ny, nx, num});
//         }
//     }
//     return ans;
// }

// int main()
// {
//     input();

//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 9; j++)
//         {
//             if (hive[i][j] == 1)
//             {
//                 oneN = max(bfs(i, j, 1), oneN);
//             }

//             if (hive[i][j] == 2)
//             {
//                 twoN = max(bfs(i, j, 2), twoN);
//             }

//             if (hive[i][j] == 3)
//             {
//                 threeN = max(bfs(i, j, 3), threeN);
//             }

//             if (hive[i][j] == 4)
//             {
//                 fourN = max(bfs(i, j, 4), fourN);
//             }
//         }
//     }

//     int ans = max({oneN, twoN, threeN, fourN});

//     if (oneN > twoN && oneN > threeN && oneN > fourN)
//     {
//         ans *= 1;
//     }
//     else if (twoN > oneN && twoN > threeN && twoN > fourN)
//     {
//         ans *= 2;
//     }
//     else if (threeN > oneN && threeN > twoN && threeN > fourN)
//     {
//         ans *= 3;
//     }
//     else if (fourN > oneN && fourN > threeN && fourN > twoN)
//     {
//         ans *= 4;
//     }

//     cout << ans;
//     return 0;
// }

/*
Issues in the Current Code:
Initialization of Counters: The counters oneN, twoN, threeN, fourN are not initialized at the beginning, which can lead to undefined behavior.

Use of Specific Variables for Each Bee Type: You are using separate variables to count each bee type's maximum connected component. This approach does not scale well if the number of bee types increases.

Incorrect Calculation of ans: The current method of calculating the final answer can be simplified by maintaining the maximum number directly during the search and using it to compute the final answer.

Resetting Visited Array: The visited array is not reset between different BFS runs for different components. This might cause some cells to be marked visited when they shouldn't be, leading to incorrect results.

General Approach: The BFS should handle any bee type generically without hardcoding for types 1, 2, 3, and 4.
*/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int hive[4][9];
int visited[4][9];
struct Node
{
    int y;
    int x;
    int num;
};

void input()
{
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> hive[i][j];
        }
    }
}

int bfs(int y, int x, int num)
{
    queue<Node> q;
    q.push({y, x, num});
    visited[y][x] = 1;

    int size = 1; // Start with the first node

    int ydir[] = {-1, 0, 1, 0};
    int xdir[] = {0, -1, 0, 1};

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 9 || visited[ny][nx])
                continue;

            if (hive[ny][nx] != num)
                continue;

            visited[ny][nx] = 1;
            size++;
            q.push({ny, nx, num});
        }
    }
    return size;
}

int main()
{
    input();

    int maxCount = 0; // To store the largest number of connected cells
    int maxType = 0;  // To store the bee type that has the maximum count

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (hive[i][j] != 0 && !visited[i][j])
            {
                int beeType = hive[i][j];
                int count = bfs(i, j, beeType);

                if (count > maxCount)
                {
                    maxCount = count;
                    maxType = beeType;
                }
            }
        }
    }

    cout << maxCount * maxType << endl;
    return 0;
}
