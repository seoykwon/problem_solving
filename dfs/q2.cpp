#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> graph[101]; // 그래프를 인접 리스트로 표현
bool visited[101];      // 방문 여부를 체크하는 배열
vector<int> preorder_result; // 전위 순회 결과 저장
vector<int> postorder_result; // 후위 순회 결과 저장

void input(int& start) {
    int N, K;
    cin >> N >> K;
    cin >> start;
    
    for (int i = 0; i < K; i++) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
    }
    
    // 노드 번호가 큰 순서로 방문하기 위해 각 리스트를 내림차순으로 정렬
    for (int i = 1; i <= N; i++) {
        sort(graph[i].rbegin(), graph[i].rend());
    }
}

void dfs_preorder(int node) {
    visited[node] = true;
    preorder_result.push_back(node);
    
    for (int next : graph[node]) {
        if (!visited[next]) {
            dfs_preorder(next);
            visited[next] = 0;
        }
    }
}

void dfs_postorder(int node) {
    visited[node] = true;
    
    for (int next : graph[node]) {
        if (!visited[next]) {
            dfs_postorder(next);
            visited[next] = 0;
        }
    }
    
    postorder_result.push_back(node);
}

int main() {
    int start;
    input(start);
    
    // 전위 순회 실행
    // fill(visited, visited + 101, false); // 방문 배열 초기화
    dfs_preorder(start);
    
    // 후위 순회 실행
    // fill(visited, visited + 101, false); // 방문 배열 초기화
    dfs_postorder(start);
    
    // 전위 순회 결과 출력
    for (int node : preorder_result) {
        cout << node << " ";
    }
    cout << endl;
    
    // 후위 순회 결과 출력
    for (int node : postorder_result) {
        cout << node << " ";
    }
    cout << endl;
    
    return 0;
}
