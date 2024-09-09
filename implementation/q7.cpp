#include <iostream>
#include <algorithm>
using namespace std;

int N;
int Q;
int color, y11, x1, y2, x2;
int board[11][11];
int dp[11][11];


int main(){
    // freopen("input.txt", "r", stdin);
    cin >> N;
    cin >> Q;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            board[i][j] = 0;
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= Q; i++){
        cin >> color >> y11 >> x1 >> y2 >> x2;

        int yl = max(y11, y2);
        int xl = max(x1, x2);
        int ym = min(y11, y2);
        int xm = min(x1, x2);

        for (int i = ym; i <= yl; i++){
            for (int j = xm; j <= xl; j++){
                if (color > board[i][j]){
                    board[i][j] = color;
                }
            }
        }
    }

    int maxSquare = 0;

    // 동적 계산법을 이용하여 최대 정사각형 크기 찾기
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (board[i][j] != 0){
                if (i == 0 || j == 0){
                    dp[i][j] = 1;
                }
                else {
                    if (board[i][j] == board[i-1][j] && board[i][j] == board[i][j-1] && board[i][j] == board[i-1][j-1]){
                        dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                    }
                    else {
                        dp[i][j] = 1;
                    }
                }
                maxSquare = max(maxSquare, dp[i][j]);
            }
        }
    }

    cout << maxSquare * maxSquare << endl;
    return 0;
}

// ################## 강사님 코드 #############################
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm> 
using namespace std;

int n; 
int q; 
int MAP[10][10];

struct Pos {
	int y;
	int x; 
};

bool cmp(Pos a, Pos b) {
	if (a.y < b.y)
		return true;
	if (a.y > b.y)
		return false;
	if (a.x < b.x)
		return true;
	if (a.x > b.x)
		return false;
	return false; 
}

void color(Pos a, Pos b, int c) {
	int sty, stx; 
	if (a.y < b.y)
		sty = a.y;
	else
		sty = b.y; 
	if (a.x < b.x)
		stx = a.x;
	else
		stx = b.x; 
	int ylen = abs(a.y - b.y);
	int xlen = abs(a.x - b.x); 
	for (int i = sty; i <= sty + ylen; i++) {
		for (int j = stx; j <= stx + xlen; j++) {
			if(MAP[i][j] == 0 || MAP[i][j] < c)
				MAP[i][j] = c; 
		}
	}
}

int findmax() {
	// 크기 설정 
	for (int k = n; k >= 1; k--) {
		// 시작 위치 설정 
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (MAP[i][j] == 0)
					continue;
				int base = MAP[i][j];
				// 해당 크기만큼의 크기 확인
				int flag = 0;
				int cnt = 0; 
				for (int y = i; y < i + k; y++) {
					for (int x = j; x < j + k; x++) {
						if (y >= n || x >= n) {
							flag = 1;
							break;
						}
						if (MAP[y][x] != base) {
							flag = 1;
							break;
						}
					}
					if (flag == 1) {
						break;
					}
				}
				// 여기까지왔다면 최대 크기 확인됨
				if (flag == 0) {
					return k * k;
				}
			}
		}
	}
}

int main() {

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> n;
	cin >> q; 
	for (int i = 0; i < q; i++) {
		int y1, x1, y2, x2, c; 
		cin >> c >> y1 >> x1 >> y2 >> x2;
		Pos A = { y1, x1 };
		Pos B = { y2, x2 };
		color(A, B, c); 
	}
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		cout << MAP[i][j];
	//	}
	//	cout << '\n';
	//}
	int ans = findmax();
	cout << ans; 
}