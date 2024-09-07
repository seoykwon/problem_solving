// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>

// using namespace std;

// // 방향 벡터 (상, 하, 좌, 우)
// int dx[4] = {-1, 1, 0, 0};
// int dy[4] = {0, 0, -1, 1};

// int main()
// {
//     // freopen("input.txt", "r", stdin);
//     int N, M;
//     cin >> N >> M;

//     // 밭의 상태 입력 받기
//     vector<vector<int>> farm(N, vector<int>(M));
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < M; j++)
//         {
//             cin >> farm[i][j];
//         }
//     }

//     // 시작 위치 입력 받기
//     int start_x, start_y;
//     cin >> start_x >> start_y;

//     // BFS를 위한 큐 (날짜, x, y)
//     queue<pair<int, pair<int, int>>> q;

//     // 꽃이 핀 여부를 확인하는 배열
//     vector<vector<bool>> visited(N, vector<bool>(M, false));

//     // 꽃이 피는 첫 위치를 큐에 넣고, 방문 처리
//     q.push({1, {start_x, start_y}});
//     visited[start_x][start_y] = true;

//     // 날짜별로 살아있는 꽃의 개수를 기록할 배열
//     vector<int> flowers_count(1000001, 0);

//     // BFS 시작
//     while (!q.empty())
//     {
//         int day = q.front().first;       // 현재 날짜
//         int x = q.front().second.first;  // 현재 위치 (x)
//         int y = q.front().second.second; // 현재 위치 (y)
//         q.pop();

//         // 해당 위치의 비옥함
//         int fertility = farm[x][y];

//         // 꽃이 비옥함만큼의 날 동안 살아있음
//         for (int i = day; i < day + fertility; i++)
//         {
//             flowers_count[i]++;
//         }

//         // 상, 하, 좌, 우로 씨앗을 퍼뜨림
//         for (int i = 0; i < 4; i++)
//         {
//             int nx = x + dx[i];
//             int ny = y + dy[i];

//             // 범위를 벗어나지 않고, 아직 방문하지 않은 곳에 씨앗을 퍼뜨림
//             if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && farm[nx][ny] > 0)
//             {
//                 visited[nx][ny] = true;
//                 q.push({day + 1, {nx, ny}});
//             }
//         }
//     }

//     // 가장 화려한 꽃밭을 찾음 (가장 많은 꽃이 살아있는 날)
//     int max_day = 0;
//     int max_flowers = 0;
//     for (int i = 0; i < flowers_count.size(); i++)
//     {
//         if (flowers_count[i] > max_flowers)
//         {
//             max_flowers = flowers_count[i];
//             max_day = i;
//         }
//     }

//     // 결과 출력
//     cout << max_day << "일" << endl;
//     cout << max_flowers << "개" << endl;

//     return 0;
// }

// // time limit

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 방향 벡터 (상, 하, 좌, 우)
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main()
{
    int N, M;
    cin >> N >> M;

    // 밭의 상태 입력 받기
    vector<vector<int>> farm(N, vector<int>(M));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> farm[i][j];
        }
    }

    // 시작 위치 입력 받기
    int start_x, start_y;
    cin >> start_x >> start_y;

    // BFS를 위한 큐 (날짜, x, y)
    queue<pair<int, pair<int, int>>> q;

    // 꽃이 핀 여부를 확인하는 배열
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    // 변화량을 기록할 배열 (스위핑 기법)
    vector<int> flower_changes(1000001, 0);

    // 꽃이 피는 첫 위치를 큐에 넣고, 방문 처리
    q.push({0, {start_x, start_y}});
    visited[start_x][start_y] = true;

    // BFS 시작
    while (!q.empty())
    {
        int day = q.front().first;       // 현재 날짜
        int x = q.front().second.first;  // 현재 위치 (x)
        int y = q.front().second.second; // 현재 위치 (y)
        q.pop();

        // 해당 위치의 비옥함
        int fertility = farm[x][y];

        // 꽃이 비옥함만큼의 날 동안 살아있음
        flower_changes[day]++;             // 꽃이 피기 시작
        flower_changes[day + fertility]--; // 꽃이 죽는 날

        // 상, 하, 좌, 우로 씨앗을 퍼뜨림
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 범위를 벗어나지 않고, 아직 방문하지 않은 곳에 씨앗을 퍼뜨림
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && farm[nx][ny] > 0)
            {
                visited[nx][ny] = true;
                q.push({day + 1, {nx, ny}});
            }
        }
    }

    // 누적 합을 통해 가장 화려한 꽃밭을 찾음
    int max_flowers = 0;
    int max_day = 0;
    int current_flowers = 0;

    for (int i = 0; i < flower_changes.size(); i++)
    {
        current_flowers += flower_changes[i];
        if (current_flowers > max_flowers)
        {
            max_flowers = current_flowers;
            max_day = i;
        }
    }

    // 결과 출력
    cout << max_day << "일" << endl;
    cout << max_flowers << "개" << endl;

    return 0;
}
// runtime error -> possible excessive memory usage
