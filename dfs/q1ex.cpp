#include <iostream>
#include <vector>

using namespace std;

int n;
int arr[10][10];
int visited[10][10];
int start, dest;


void input(){
    cin >> n;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
    cin >> start >> dest;
}

void dfs(int now, int y, int x){
    visited[y][x] = 1;

    

}

int main(){
    input();

    dfs(start, 0, 0);
}