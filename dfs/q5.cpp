// #include <iostream>
// using namespace std;

// int n;
// int arr[1000][1000];
// int visited[1000];
// int minVal = 999999, maxVal, dis;

// void dfs(int cur, int dis)
// {
//     if (cur == 0 && dis > 0)
//     {
//         if (dis < minVal)
//         {
//             minVal = dis;
//         }
//         cout << dis << " ";
//         return;
//     }

//     for (int i = 0; i < n; i++)
//     {
//         if (arr[cur][i] == 0)
//         {
//             continue;
//         }
//         if (visited[i])
//         {
//             continue;
//         }
//         visited[i] = 1;
        
//         dfs(i, dis + arr[cur][i]);
//         visited[i] = 0;
//     }
// }

// int main()
// {
//     cin >> n;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             cin >> arr[i][j];
//         }
//     }

//     visited[0] = 1;
//     dfs(0, 0);
//     cout << minVal << endl;
// }

#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int n;
int arr[102][102];
bool visited[102];
int minVal = INT_MAX;

void dfs(int cur, int count, int cost) {
    if (count == n && arr[cur][0] > 0) {
        minVal = min(minVal, cost + arr[cur][0]);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && arr[cur][i] > 0) {
            visited[i] = true;
            dfs(i, count + 1, cost + arr[cur][i]);
            visited[i] = false;
        }
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }

    visited[0] = true;
    dfs(0, 1, 0);

    cout << minVal << endl;

    return 0;
}

// #include<iostream>
// #include<algorithm>
// using namespace std;

// int MAP[12][12];
// int visited[12]; 
// int n; 
// int sum = 0;
// int ans = 2143567890; 
// int cnt = 0; 

// void dfs(int node) {

//     // 시작 노드로 돌아왔고, 모든 노드를 방문했다면
//     if (cnt == n && node == 0) 
//         if (sum < ans)
//             ans = sum; 
//     // 시작 노드로 돌아와야 하기 때문에, 시작 노드를 visited 체크하지 않음.
//     for (int i = 0; i < n; i++) {
//         if (visited[i] == 1)
//             continue;
//         if (MAP[node][i] == 0)
//             continue;
//         // 중간 가지치기 -> 없으면 시간초과
//         if (sum + MAP[node][i] > ans)
//             continue;
//         // pre -> 들어가면서 비용 누적, 방문 기록
//         sum += MAP[node][i];
//         // 방문한 노드 개수 기록 
//         cnt++; 
//         visited[i] = 1; 
//         dfs(i);
//         // post -> 나오면서 비용, 방문 기록 해제
//         sum -= MAP[node][i];
//         visited[i] = 0; 
//         cnt--;
//     }
// }

// int main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL); 
//     cin >> n;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> MAP[i][j];
//         }
//     }
//     dfs(0); 
//     cout << ans; 
// }
