#include <iostream>
#include <queue>

using namespace std;

int n;
int arr[11][11];
int visited[11];


void input(){
    cin >> n;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
}

void bfs(int start){
    queue <int> q;
    q.push(start);
    visited[start] = 1;

    while(!q.empty()){
        int now = q.front(); q.pop();
        
        cout << now << " ";
        for(int i = 0; i < n; i++){
            if (visited[i]) {continue;}
            if (arr[now][i] == 1) {
                int next = i;
                visited[next] = 1;
                q.push(next);
            }    
        }

    }
}

int main(){
    input();

    bfs(0);
}

// #include <iostream>
// #include <queue>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int n;
// int arr[11][11];
// int visited[11] = {0};

// void input() {
//     cin >> n;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> arr[i][j];
//         }
//     }
// }

// void bfs(int start) {
//     queue<int> q;
//     q.push(start);
//     visited[start] = 1;

//     while (!q.empty()) {
//         int now = q.front();
//         q.pop();

//         cout << now << " ";

//         vector<int> neighbors;
//         for (int i = 0; i < n; i++) {
//             if (arr[now][i] == 1 && !visited[i]) {
//                 neighbors.push_back(i);
//             }
//         }

//         sort(neighbors.begin(), neighbors.end());

//         for (int next : neighbors) {
//             if (!visited[next]) {
//                 visited[next] = 1;
//                 q.push(next);
//             }
//         }
//     }
// }

// int main() {
//     input();
//     bfs(0);
//     return 0;
// }
