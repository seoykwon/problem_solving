#include <iostream>

using namespace std;

int n;
int arr[101][101] = {0};

void input(){
    cin >> n;
    for(int i = 0; i<n ;i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
}

void dfs(int now)
{
	cout << now << " ";

	for (int i = 0; i < n; i++) {
		if (arr[now][i] == 1) {
			dfs(i);
		}
	}
}

int main(){
    input();
    dfs(0);
}