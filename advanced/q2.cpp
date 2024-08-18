#include <iostream>
#include <vector>

using namespace std;

int t, n;
int cnt;
int board[51][51] = {0};
int s = 0;

struct po{
    int y;
    int x;
    int num;
};
struct jjol{
    int y;
    int x;
    int num;
};

po p;
vector <jjol> jj;

void input(){
    cin >> n;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            board[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> board[i][j];

            if (board[i][j] == 2){
                p = {i, j, 2};
            }
            else if (board[i][j] == 1){
                jj.push_back({i, j, 1});
            }
        }
    }
}

int dfs(int y, int x){
    if (board[y][x] == 1){
        board[y][x] = 0;
        return 1;
    }
    
    int trial = 3;

    int ydir[4] = {1, -1, 0, 0};
    int xdir[4] = {0, 0, -1, 1};

    while(trial--){
        for (int i = 0; i < 4; i++){

            int ny = y + ydir[i];
            int nx = x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

            if(board[ny][nx] == 1){
                
            }
         
        }
    }
}

int main(){
    cin >> t;

    for (int i = 1; i <= t; i++){
        cnt = 0;
        input();

        s = jj.size();

        for (int j = 0; j < s; j++){
            cnt += dfs(p.y, p.x);
        }

        cout << "#" << t << " " << cnt << endl;
    }
}