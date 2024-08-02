#include <iostream>
#include <queue>

using namespace std;

int graph[6][6] = {
    {0, 0, 1, 0, 1, 1},
    {1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};

int from, to;
queue <int> q;
int visited[6];

void bfs(int start, int dest){
    // 대기열
    // 시작 노드 등록
    q.push(start);

    for (int i = 0; i < 6; i++){
        visited[i] = -1;
    }
    visited[start] = 0;

    // 큐가 비기전까지 반복
    while(!q.empty()){
        // 맨앞노드 확인 및 추출
        int now = q.front(); q.pop();
        if (now == dest){
            cout << visited[now] << endl;
            // cout << now << endl;
            return;
        }
        for (int next = 0; next <= 6; next++){
            if (graph[now][next] == 0) continue;
            if (visited[next] > -1) continue;
            visited[next] = visited[now] + 1;
            q.push(next);
        }
    }
    cout << 0 << endl;
}

int main(){
    cin >> from >> to;

    bfs(from-1, to-1);
}