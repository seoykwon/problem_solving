#include<iostream>
#include<vector>
using namespace std;

int mat[10][10];
int visited[7];
vector<int>v[7];
vector<int>path;
int N, M;
/*
6 5
1 2
2 4
1 3
3 5
5 6
*/

/*
4 5
1 2
2 4
4 1
2 3
3 4
*/
//int main() {
//	cin >> N >> M;
//	for (int i = 0; i < M; i++) {
//		int from, to;
//		cin >> from >> to;
//		mat[from][to] = 1;// from 에서 to 연결 되어 있다. 연결 여부를 저장
//	}
//	for (int i = 0; i <= N; i++) {
//		for (int j = 0; j <= N; j++) {
//			cout << mat[i][j] << " ";
//		}
//		cout << "\n";
//	}
//	//Query 
//	int a, b;
//	cin >> a >> b;
//	cout << mat[a][b];// 연결되어 있다면 1
//	// 조회가 빠르다.
//
//
//}

void dfs(int now) {
	cout << now << " ";
	//종료조건 작성 option 완전탐색(모든 노드를 방문 하지 않고 끄읏)
	// 종료 조건 미작성 완전탐색(모든 노드방문)
	
	//if (종료조건)return;
	// 특정 종료 조건을 설정하는 경우 사용
	//if (now == 5) return;
	/*if (now == 4) {
		for (int i = 0; i < path.size(); i++) {
			cout << path[i] << " ";
		}
		cout << "\n";
		return;
	}*/

	//now에서 갈수 있는 next를 뽑고 가라
	for (int i = 0; i < v[now].size(); i++) {
		int next = v[now][i];
		path.push_back(next);// next 기록
		if (visited[next] == 1)continue;
		//처리
		visited[next] = 1; // 다음 노드 next를 방문할거다 라고 기록하고 시작
		//가라
		dfs(next);
		//복구
		//path.pop_back();
		//visited[next] = 0; // visited 체크하는 경우
		                   // 모든 노드를 탐색하는 경우의 수 하나만 보겠다.
							// visited 복구 하는 경우
							// 모든 노드를 탐색하는 경우의 수 다른 것도 보겠다.
	}
	
}


int main() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;
		v[from].push_back(to);
	}
	/*for (int i = 0; i < N; i++) {
		cout << i << " ";
		for (int j = 0; j < v[i].size(); j++) {
			cout << v[i][j]<< " ";
		}
		cout << "\n";
	}*/
	visited[1] = 1; //방문할거다~!!
	path.push_back(1);
	dfs(1);

}