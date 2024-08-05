#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
	int num;
	long long cost;
};

vector<Node>v[100001];
int n, m, k;
long long dist[100001];

void bfs(int node) {
	queue<Node>q;
	q.push({ node, 0 });

	dist[node] = 0;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < v[now.num].size(); i++) {
			Node next = v[now.num][i];
			dist[next.num] = dist[now.num] + next.cost;
			q.push({ next.num, next.cost });
		}
	}

	int cnt = 0;
	for (int i = 2; i <= n; i++) {
		if (dist[i] > 0 && dist[i] <= k)
			cnt++;
	}
	cout << cnt;
}

int main() {
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to, cost });
	}
	bfs(1);

}