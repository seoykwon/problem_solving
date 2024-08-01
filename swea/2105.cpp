#include<iostream>
#include<vector>
using namespace std;

int M[30][30];
int visited[110];
int T;
int N;
int destRow;
int destCol;
int ans;
vector<int>path;
//우하 좌하 좌상 우상
int dr[] = {-1,-1,1,1};
int dc[] = {1,-1,-1,1};

void init() {
	ans = 0;
	path.clear();
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			M[i][j] = -1;
		}
	}
	for (int i = 0; i < 110; i++) {
		visited[i] = 0;
	}
}
void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> M[i][j];
		}
	}// 경로를 벗어나는 경우 
	 // 쉽게 처리하기 위한 목적

}
void dfs(int row, int col, int dir) { // now 는 row,col좌표에 dir 방향이다~!!

	//기저
	if (row == destRow && col == destCol) {
		if (ans < path.size())
			ans = path.size();
		return;
	}

	for (int ndir = dir; ndir <= dir + 1; ndir++) {
		//dir == ndir 같은 방향 dir+1 == ndir 방향 꺽어서
		if (ndir >= 4)continue;
		int nr = row + dr[ndir];
		int nc = col + dc[ndir];
	//판별
		if (visited[M[nr][nc]] == 1)continue;
		if (M[nr][nc] == -1) continue;
	//처리
		path.push_back(M[nr][nc]);
		visited[M[nr][nc]] = 1; // index : 카페 번호 value : 경로상에 같은 카페가 있는가?
	//가라
		dfs(nr, nc, ndir); // nr, nc , ndir
	//복구
		path.pop_back();
		visited[M[nr][nc]] = 0; // 다양한 경로를 가보기 위해 복구 처리
	}
	
}
void solution() {
	//모두 해보기 dfs돌리자~!!
	for (int row = 1; row <= N; row++) {
		for (int col = 1; col <= N; col++) {
			//도착지 설정 필요
			destRow = row + 1;
			destCol = col - 1;
			//시작점 세팅
			visited[M[row][col]] = 1;
			path.push_back(M[row][col]);
			dfs(row, col, 0);
			
			visited[M[row][col]] = 0;
			path.pop_back();
		}
	}
	if (ans < 4)
		ans = -1;
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		solution();
		cout << "#" << tc << " " << ans << "\n";
	}
}