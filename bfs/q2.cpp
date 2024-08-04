#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int mat[11][11]; 
int n, m, k;

int dist[11];

void bfs(int node) {
	queue<int>q;
	q.push(node);
	
	dist[node] = 0; 
	
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		
		for (int i = 0; i <= n; i++) {
			int next = i;
			if (mat[now][next] == 0)
				continue;
			dist[next] = dist[now] + mat[now][next]; 
			q.push(next); 
		}
	}

	for (int i = 1; i <= n; i++) {
		if (dist[i] > 0 && dist[i] <= k)
			cout << i << " ";
	}
}

int main() {
	cin >> n >> m >> k; 
	for (int i = 0; i < m; i++) {
		int from, to, cost; 
		cin >> from >> to >> cost;
		mat[from][to] = cost; 
	}
	bfs(0); 

}