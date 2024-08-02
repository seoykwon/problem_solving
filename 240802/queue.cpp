#include <iostream>
#include <queue>
#include <vector>

using namespace std;

queue <int> q;

/*
DFS: 재귀코드
-> 한 방향으로 갈 수 있는 데까지 가보고 다른 경로 또 탐색
-> 다양한 경로 -> 가장 긴 경로
-> 효율을 높이기 위한 백트래킹/ 기저 조건 설정

BFS: 큐를 사용 (함수가 필수가 아님)
-> now 기준 발견되는 순서대로 간다
-> 최대한 적은 노드의 개수를 거쳐서 가는 방법을 알 수 있다
-> 해당 경로 외에 다른 경로를 알지는 못함
-> 최단 경로

BFS: 특정 노드 기준 최단경로
DFS: 특정 노드 기준 모든 경로 
둘 다 가중치가 없다. 서로 같다.

Dijkstra: from->to 최소비용 (특정 노드에 가중치 존재)
floyd warshall: 가중치가 모든 노드에게 있다.
*/

// int main() {
//     // 큐 명령어 확인
//     // 데이터 추가
//     q.push(1);
//     q.push(10);
//     q.push(30);

//     // 큐에 맨앞에 데이터 확인
//     cout << q.front() << " ";
//     // 데이터 추출
//     q.pop();
//     cout << q.front() << " ";
//     q.pop();

//     // 큐가 비었는지 확인
//     cout << q.empty();
//     q.pop();
//     cout << q.empty();
// }

int N, M, Q;
vector <int> alis[10];

int mat[10][10];
int visited[10];

// // 인접 리스트
// void bfs(int start){
//     // 1. 대기열 준비
//     queue <int> q;
//     // 2. 시작노드 큐에 등록
//     q.push(start);
//     // 큐가 비기전까지 3-5 반복
//     while (!q.empty()){
//         // 3. 맨앞에 노드 확인 및 추출 (now 위치에 있다)
//         int now = q.front(); q.pop();
//         cout << now << " ";
//         // 4. 추출한 노드와 인접/연결되어 있던 다음(next) 노드 탐색
//         for (int i = 0; i < alis[now].size(); i++){
//             // 5. next 후보지 큐에 등록
//             int next = alis[now][i];
//             q.push(next);
//         } 
//     }
// }

// 인접 행렬 방식
void bfs(int start, int dest){
    // 1. 대기열
    queue <int> q;
    // 2. 시작 노드 등록
    q.push(start);
    for(int i = 0; i < 10; i++){
        visited[i] = -1;
    }
    visited[start] = 0; // 방문할 예정. 기록하고 시작

    // 6. 큐가 비기전까지 3-5 반복
    while (!q.empty()){
       // 3. 맨앞노드 확인 및 추출(now)
        int now = q.front(); q.pop();
        if (now == dest){
            cout << visited[now] << endl;
        }

        cout << now << " ";
        // 4. 다음 next 찾기
        for (int next = 0; next < N; next++){
            // 5. next 큐에 등록 
            if (mat[now][next] == 0) continue;
            // if (visited[next] == 1) continue;
            // if (visited[next] > 0) continue;
            if (visited[next] > -1) continue;

            // visited[next] = 1;
            visited[next] = visited[now] + 1;
            q.push(next);

        }
        
    }
    cout << endl;
    for (int i = 1; i <= N; i++){
        cout << i << " : " << visited[i] << endl;
    }
}

int main(){
    cin >> N >> M;
    for (int i = 0; i < M; i++){
        int from, to;
        cin >> from >> to;
        // alis[from].push_back(to);
        mat[from][to] = 1;
        mat[to][from] = 1;
    }
    cin >> Q;
    for (int i = 0; i < Q; i++){
        int from, to;
        cin >> from >> to;
        bfs(from, to);
    }
    // bfs(1);
}