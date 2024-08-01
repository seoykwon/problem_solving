// #include <iostream>
// #include <vector>
// #include <stack>

// using namespace std;

// // DFS 함수 정의
// void dfs(const vector<vector<int>>& graph, int start, vector<bool>& visited, vector<int>& order) {
//     stack<int> s;
//     s.push(start);

//     while (!s.empty()) {
//         int node = s.top();
//         s.pop();
        
//         if (!visited[node]) {
//             visited[node] = true;
//             order.push_back(node);
            
//             // 인접 노드를 역순으로 스택에 추가
//             for (int i = graph.size() - 1; i >= 0; --i) {
//                 if (graph[node][i] == 1 && !visited[i]) {
//                     s.push(i);
//                 }
//             }
//         }
//     }
// }

// int main() {
//     int n;
//     cin >> n;

//     vector<vector<int>> graph(n, vector<int>(n));
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < n; ++j) {
//             cin >> graph[i][j];
//         }
//     }

//     vector<bool> visited(n, false);
//     vector<int> order;

//     // DFS 탐색 시작
//     dfs(graph, 0, visited, order);

//     // 결과 출력
//     for (int i = 0; i < order.size(); ++i) {
//         cout << order[i];
//         if (i < order.size() - 1) {
//             cout << " ";
//         }
//     }
//     cout << endl;

//     return 0;
// }


#include <iostream>
using namespace std;

int map[10][10];
int n;

void input()
{
	cin >> n;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> map[y][x];
		}
	}
}

void run(int now)
{
	cout << now << " ";

	for (int i = 0; i < n; i++) {
		if (map[now][i] == 1) {
			run(i);
		}
	}
}

int main()
{
	input();
	run(0);

	return 0;
}