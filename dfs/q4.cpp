// #include <iostream>
// #include <vector>

// using namespace std;

// int n;
// int arr[100][100];
// int start, dest;

// int max_len = 0;
// int min_len = 0;

// void input(){
//     cin >> n;
//     for(int i = 0; i < n; i++){
//         for(int j = 0; j < n; j++){
//             int tmp;
//             cin >> tmp;
//             arr[i][j] = tmp;
//         }
//     }
//     cin >> start >> dest;
// }

// void dfs(int start, int dest){
//     if (start == dest){
//         cout << min_len << endl;
//         cout << max_len << endl;
//         return;
//     }
	
// 	//if (종료조건)return;
// 	// 특정 종료 조건을 설정하는 경우 사용
// 	//if (now == 5) return;
// 	/*if (now == 4) {
// 		for (int i = 0; i < path.size(); i++) {
// 			cout << path[i] << " ";
// 		}
// 		cout << "\n";
// 		return;
// 	}*/

// 	//now에서 갈수 있는 next를 뽑고 가라
// 	for (int i = 0; i < v[now].size(); i++) {
// 		int next = v[now][i];
// 		path.push_back(next);// next 기록
// 		if (visited[next] == 1)continue;
// 		//처리
// 		visited[next] = 1; // 다음 노드 next를 방문할거다 라고 기록하고 시작
// 		//가라
// 		dfs(next);
// 		//복구
// 		//path.pop_back();
// 		//visited[next] = 0; // visited 체크하는 경우
// 		                   // 모든 노드를 탐색하는 경우의 수 하나만 보겠다.
// 							// visited 복구 하는 경우
// 							// 모든 노드를 탐색하는 경우의 수 다른 것도 보겠다.
// 	}
// }

// int main(){
//     input();

//     dfs(start, dest);
// }

#include <iostream>
using namespace std;

int n;
int arr[1000][1000];
int visited[1000];
int st, en;
int minVal = 999999, maxVal, dis;

void dfs(int cur, int dis)
{
    if (cur == en)
    {
        if (dis < minVal)
        {
            minVal = dis;
        }
        if (dis > maxVal)
        {
            maxVal = dis;
        }
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[cur][i] == 0)
        {
            continue;
        }
        if (visited[i])
        {
            continue;
        }
        visited[i] = 1;
        dfs(i, dis + arr[cur][i]);
        visited[i] = 0;
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }
    cin >> st >> en;

    visited[st] = 1;
    dfs(st, 0);
    cout << minVal << endl
         << maxVal;
}