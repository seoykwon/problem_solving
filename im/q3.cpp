
#include <iostream>
#include <vector>

using namespace std;

int arr[101][101] = {0,};
int n;
int t;
int p;
int maxCnt = 0;
// int ans[101][101] = {0,};
int current = 0;

void input() {
    cin >> n >> p;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            arr[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
};

void find(){
    int ydir[4] = {-1, 0, 1, 0};
    int xdir[4] = {0, -1, 0, 1};

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            current = arr[i][j];
            for (int d = 0; d < 4; d++){
               for (int k = 1; k <= p; k++){
                   int ny = i + ydir[d] * k;
                   int nx = j + xdir[d] * k;

                   if (ny < 0 || nx < 0 || ny >= n || nx >= n) break;

                   current += arr[ny][nx];
               } 
            } 
            maxCnt = max(maxCnt, current); 
        }
    }
}

int main(){
    // freopen("input.txt", "r", stdin);
    cin >> t;

    for (int i = 1; i <= t; i++){
        input();
        maxCnt = 0;
        find();

        cout << "#" << i << " " << maxCnt << endl;
    }
}

/*
문제
1. ans[i][j] 배열을 사용하여, 중복된 계산이 발생할 수 있다. 왜냐하면 ans[i][j]를 매번 초기화 하지 않았기 때문
2. 굳이 필요하지 않은 정보들을 따로 저장해 둘 필요가 없다
3. k가 0에서부터 시작하면 arr[ny][nx]가 중복되어 저장된다
*/

// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int arr[101][101] = {0,}; // 마을 바이러스 수
// int n, p, t;
// int maxCnt = 0;

// void input() {
//     cin >> n >> p;

//     // 바이러스 데이터 입력
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> arr[i][j];
//         }
//     }
// }

// void find() {
//     maxCnt = 0;

//     // 마을의 모든 위치에 대해 차르봄바를 떨어뜨려본다
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             int currentCnt = arr[i][j]; // 현재 위치에서의 바이러스 수 포함

//             // 상하좌우 4방향으로 P 거리만큼 퍼져나가며 바이러스 합산
//             for (int d = 1; d <= p; d++) {
//                 // 위쪽
//                 if (i - d >= 0) currentCnt += arr[i - d][j];
//                 // 아래쪽
//                 if (i + d < n) currentCnt += arr[i + d][j];
//                 // 왼쪽
//                 if (j - d >= 0) currentCnt += arr[i][j - d];
//                 // 오른쪽
//                 if (j + d < n) currentCnt += arr[i][j + d];
//             }

//             // 최대값 갱신
//             maxCnt = max(maxCnt, currentCnt);
//         }
//     }
// }

// int main() {
//     // freopen("input.txt", "r", stdin);
//     cin >> t;

//     for (int i = 1; i <= t; i++) {
//         input();
//         find();

//         cout << "#" << i << " " << maxCnt << endl;
//     }

//     return 0;
// }
