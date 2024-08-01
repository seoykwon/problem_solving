// #include <iostream>
// using namespace std;

// const int MAX_N = 10;
// int map[MAX_N][MAX_N];
// int n;
// int path[MAX_N];
// bool visited[MAX_N];

// // 입력 함수
// void input() {
//     cin >> n;
//     for (int y = 0; y < n; y++) {
//         for (int x = 0; x < n; x++) {
//             cin >> map[y][x];
//         }
//     }
// }

// // DFS 함수
// void run(int node, int depth) {
//     // 경로의 길이가 3이 되면 Level 2에 도착한 것
//     if (depth == 3) {
//         for (int i = 0; i < depth; i++) {
//             cout << path[i] << " ";
//         }
//         cout << endl;
//         return;
//     }

//     for (int i = 0; i < n; i++) {
//         if (map[node][i] == 1 && !visited[i]) {
//             visited[i] = true;
//             path[depth] = i;
//             run(i, depth + 1);
//             visited[i] = false; // 백트래킹
//         }
//     }
// }

// int main() {
//     input();
//     for (int i = 0; i < n; i++) {
//         visited[i] = false;
//     }
//     visited[0] = true; // 시작 노드 방문
//     path[0] = 0;
//     run(0, 1); // 시작 노드(0)에서 깊이 1로 DFS 시작

//     return 0;
// }


#include <iostream>
#include <string>
using namespace std;

int n;
int map[10][10];
int path[10];

void input()
{
	cin >> n;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> map[y][x];
		}
	}
}

void dfs(int level, int now)
{
	if (level == 2) {
		for (int i = 0; i <= level; i++) {
			cout << path[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = 0; i < n; i++) {
		if (map[now][i] == 1) {
			path[level + 1] = i;
			dfs(level + 1, i);
			path[level + 1] = 0; // 덮어쓰면 되서 필요없음
		}
	}
}

int main()
{
	input();
	path[0] = 0;

	dfs(0, 0);

	return 0;
}