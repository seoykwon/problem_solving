#include <iostream>
#include <vector>

using namespace std;

int start;

int graph[6][6] = {
    {0, 0, 1, 1, 0, 1},
    {0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}
};
vector<int> path;
int visited[6] = {0};

void dfs(int now){
    visited[now] = 1;
    cout << now << " ";
    for(int i = 0; i < 6; i++){
        if(graph[now][i] == 1 && !visited[i])
        {
            dfs(i);
        }
    }
}

int main(){
    cin >> start;

    dfs(start);
}