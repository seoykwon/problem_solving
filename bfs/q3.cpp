#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, coco;
vector<vector<int>> adj;
vector<bool> visited;

void input() {
    cin >> N >> M;
    adj.resize(N + 1);
    visited.resize(N + 1, false);

    for (int i = 0; i < M; i++) {
        int A, B;
        cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);  // Since the relationship is bidirectional
    }
    cin >> coco;
}

int bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    int count = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        count++;

        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return count - 1;  // Exclude Coco himself
}

int main() {
    input();
    int result = bfs(coco);
    cout << result << endl;
    return 0;
}
