#include <iostream>
#include <vector>

using namespace std;

int graph[6][6] ={
    {0,0,1,0,2,0},
    {5,0,3,0,0,0},
    {0,0,0,0,0,7},
    {2,0,0,0,8,0},
    {0,0,9,0,0,0},
    {4,0,0,7,0,0}
};

int k;
int w = 0;
int visited[6] = {0};

void dfs(int now){
    visited[now] = 1;
    // cout << now << " ";
    
    
    for(int i = 0; i < 6; i++){
        if(graph[now][i] > 0 && !visited[i])
        {   
            
            w += graph[now][i];
            cout << i << " ";
            cout << w << endl;
            dfs(i);
        }
    }
}

int main(){
    cin >> k;

    cout << k << " 0" << endl; 
    dfs(k);
}

// #include<iostream>
// using namespace std; 


// int map[6][6]; 
// int start; 
// void input() {
// 	map[0][2] = 1; 
// 	map[0][4] = 2; 
// 	map[1][0] = 5; 
// 	map[1][2] = 3; 
// 	map[2][5] = 7; 
// 	map[3][0] = 2; 
// 	map[3][4] = 8; 
// 	map[4][2] = 9; 
// 	map[5][0] = 4; 
// 	map[5][3] = 7; 
// 	cin >> start; 
// }
// int visited[6]; 
// int sum; 
// void dfs(int now) {
// 	cout << now << " " << sum << endl;
// 	for (int next = 0; next < 6; next++) {
// 		if (map[now][next] == 0) continue; // 간선 x 
// 		if (visited[next] == 1) continue; 
// 		visited[next] = 1; 
// 		sum += map[now][next]; 
// 		dfs(next); 
// 	}
// }
// int main()
// {
// 	input(); 
	
// 	visited[start] = 1; 
// 	dfs(start); 
// 	return 0; 
// }