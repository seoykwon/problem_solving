#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;
int tree[11][11] = {0,};
int visited[11] = {0};

void input(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> tree[i][j];
        }
    }
}

void bfs(int node){
    

    queue <int> q;
    q.push(node);
    vector<int> result;
    
    visited[node] = 1;

    while(!q.empty()){
        
        int next = q.front();
        // unlike dfs, bfs does not change node. 
        cout << next << " ";
        q.pop();
        result.push_back(next);
        for(int i = 0; i < n; i++){
            if(tree[node][i] == 1 && !visited[i]){
                q.push(i);
                visited[i] = 1;
            }
        }
    }

    // // 결과 출력
    // for (int i = 0; i < result.size(); i++) {
    //     cout << result[i] << " ";
    // }
    // cout << endl;
}

int main(){
    input();

    bfs(0);
}

// #include <iostream>
// #include <queue>
// #include <vector>

// using namespace std;

// int n;
// int tree[11][11] = {0,};
// bool visited[11] = {false};

// void input() {
//     cin >> n;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> tree[i][j];
//         }
//     }
// }

// void bfs(int start) {
//     queue<int> q;
//     q.push(start);
//     visited[start] = true;
//     vector<int> result;

//     while (!q.empty()) {
//         int node = q.front();
//         q.pop();
//         result.push_back(node);

//         // 방문 가능한 노드를 정렬 후 큐에 삽입
//         for (int i = 0; i < n; i++) {
//             if (tree[node][i] == 1 && !visited[i]) {
//                 q.push(i);
//                 visited[i] = true;
//             }
//         }
//     }

//     // 결과 출력
//     for (int i = 0; i < result.size(); i++) {
//         cout << result[i] << " ";
//     }
//     cout << endl;
// }

// int main() {
//     input();
//     bfs(0);
//     return 0;
// }
