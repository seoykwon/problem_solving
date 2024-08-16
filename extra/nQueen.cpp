#include <iostream>
#include <vector>

using namespace std;

int n;
int group1[20][20];
int group2[20][20];
int used_col[40];
int used1[20];
int used2[20];

int answer = 0;

void func(int row){
    if (row >= n){
        answer += 1;
        return;
    }
    for (int col = 0; col < n; col++){
        // 판별
        if (used_col[col] == 1) continue;
        if (used1[group1[row][col]] == 1) continue;
        if (used2[group2[row][col]] == 1) continue;

        // 처리
        used_col[col] = 1; // index: col value: 사용여부
        used1[group1[row][col]] = 1; // index: 좌하 방향 몇번 대각선 value
        used2[group2[row][col]] = 1; // index: 우하 방향 몇번 대각선 value

        // 가라
        func(row + 1);

        // 복구
        used_col[col] = 0;
        used1[group1[row][col]] = 0;
        used2[group2[row][col]] = 0;
    }
}

void make_group1(int r, int c){
    int R = r;
    int C = c;
    while (1){
        if(R >= n || C < 0) return;
        group1[R][C] = R + C;
        R += 1;
        C -= 1;
    }
}

void make_group2(int r, int c){
    int R = r;
    int C = c;
    while (1) {
        if (R >= n || C >= n) return;
        group2[R][C] = R - C + n;
        R += 1;
        C += 1;
    }
}

int main() {
    cin >> n;
    for (int r = 0; r < n; r++){
        for (int c = 0; c < n; c++){
            if(group1[r][c] == 0){
                make_group1(r, c);
            }
        }
    }

    for (int r = 0; r < n; r++){
        for (int c = 0; c < n; c++){
            if (group2[r][c] == 0){
                make_group2(r, c);
            }
        }
    }
    func(0);
    cout << answer;

}