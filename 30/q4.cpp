#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> alis[6];
int start;
int visited[6] = {0}; // Initialize the visited array with 0s

void input() {
    alis[0].push_back(4);
    alis[1].push_back(0);
    alis[1].push_back(2);
    alis[1].push_back(5);
    alis[2].push_back(0);
    alis[2].push_back(3);
    alis[3].push_back(0);
    alis[3].push_back(1);
    alis[4].push_back(1);
    alis[4].push_back(3);
    alis[4].push_back(5);
    alis[5].push_back(2);
    alis[5].push_back(3);
    cin >> start;
}

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty()) {
        int now = q.front(); q.pop();
        cout << now << endl;

        vector<int> neighbors = alis[now];
        sort(neighbors.begin(), neighbors.end()); // Sort neighbors to visit nodes in ascending order

        for (int i = 0; i < neighbors.size(); i++) {
            int next = neighbors[i];
            if (!visited[next]) {
                q.push(next);
                visited[next] = 1;
            }
        }
    }
}

int main() {
    input();
    bfs(start);
}
