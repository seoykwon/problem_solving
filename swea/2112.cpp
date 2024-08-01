#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int T;
int D, W, K;
int film[15][25];
vector<int>path;
int cnt;
int ans = 2134567890;
void init() {
	cnt = 0;
	ans = 2134567890;
	path.clear();
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 25; j++) {
			film[i][j] = 0;
		}
	}
}
void input() {
	// D : 두께 , W : 가로 크기, K : 합격기준

	cin >> D >> W >> K;
	for (int row = 0; row < D; row++) {
		for (int col = 0; col < W; col++) {
			cin >> film[row][col];
		}
	}
}
bool isValid() {
	//지금 path대로 처리하면 가능? 합격/불합격?

	for (int col = 0; col < W; col++) {
		//세로선 하나 셀렉~!!
		int prev = film[0][col]; // 맨 윗줄의 특성확인
		int cont = 1; //연속한 갯수
		int contMax = 1; // 연속한 갯수의 최대값
		if (path[0] != -1) prev = path[0]; //약품 투입이 기록되어 있는대로 맨 윗줄 처리 

		for (int row = 1; row < D; row++) {
			int nowValue = film[row][col];
			if (path[row] != -1)
				nowValue = path[row]; //약품 투입이 기록되어 있는대로 처리 row~D-1

			if (prev == nowValue)
				cont += 1;
			else
				cont = 1;

			prev = nowValue; //그다음줄
			contMax = max(contMax, cont);
		}
		if (contMax < K) return false;
	}
	return true;
}


void func(int now) {
	//now층에서 어떻게 할것인가?
	//기저
	//if (cnt >= ans)
	//	return;
	////cnt가 최소 횟수보다 큰 경우
	if (now >= D) { //0~D-1 D(두께만큼) 필름두께만큼 약품 투입 경우의 수 확인

		if (isValid()) {
			//이번에 뽑은 약품 대로 처리할 때) 합격기준에 부합하는가?
			//합격 기준을 통과하는 case를 하나 찾았다~!!
			ans = min(ans, cnt);
		}
		return;
	}

	for (int i = -1; i <= 1; i++) { //i : -1 그대로 i: 0 A약품 i: 1 B약품
		//판별
		if (i != -1 && cnt + 1 > K)continue;// 합격 기준보다 높으면 굳이 더 좋게 만들 필요는 없다.~!
		if (i != -1 && cnt + 1 >= ans) continue; // 이미 최소값을 구했는데 더 할 필요는 없다.
		//처리
		if (i != -1) cnt += 1;
		path.push_back(i);
		//가라
		func(now + 1);
		//복구
		if (i != -1) cnt -= 1;
		path.pop_back();
	}
}
void solution() {
	func(0);
}


int main() {

	//freopen("input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		solution();
		cout << "#" << tc << " " << ans << "\n";
	}
}