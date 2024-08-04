#include <iostream>
#include <vector>

using namespace std;

int cmp;                // 컴퓨터 수
int pairs;              // 네트워크 쌍의 수
vector<int> v[101];     // 그래프 표현 (인접 리스트)
bool visited[101];      // 방문 여부 체크
int cnt = 0;            // 감염된 컴퓨터 수

void input() {
    cin >> cmp >> pairs;
    
    for (int i = 0; i < pairs; i++) {
        int from, to;
        cin >> from >> to;
        v[from].push_back(to);
        v[to].push_back(from); // 양방향 연결
    }
}

void dfs(int start) {
    visited[start] = true;
    cnt++; // 감염된 컴퓨터 수 증가
    
    for (int i = 0; i < v[start].size(); i++) {
        int next = v[start][i];
        if (!visited[next]) {
            dfs(next);
        }
    }
}

int main() {
    input();
    visited[1] = true; // 1번 컴퓨터 방문 시작
    dfs(1);

    cout << cnt - 1; // 1번 컴퓨터를 제외한 감염된 컴퓨터 수 출력
    return 0;
}
