#include <iostream>
#include <queue>

using namespace std;

int tree[6][6];
int start;
int visited[6];
vector<int>alis[10];

void input(){
    alis[0].push_back(1);
    alis[0].push_back(4);
    alis[1].push_back(2);
    alis[1].push_back(5);
    alis[2].push_back(3);
    cin >> start;
}

// void dfs(int now){
//     cout << now << " ";
//     for (int next = 0; next < 6; next++){
//         // if(visited[now] == 1) continue;
//         if(tree[now][next] == 0) continue;
//         // visited[now] = 1;
//         dfs(next);
//     }
// }


void bfs(int now){
    //1.대기열 준비
    	queue<int>q;
    	//2.시작노드 큐에 등록
    	q.push(start);
    	//->큐가 비기전까지 3~5 반복
    	while (!q.empty()) {
    		//3.맨앞에 노드 확인 및 추출(now 위치에 있다)
    		int now = q.front(); q.pop();
    		cout << now << " "; // 출력
    		//4.추출한 노드(now)와 인접/연결되어 있던 다음(next)노드 탐색
    		for (int i = 0; i < alis[now].size(); i++) {
    		   //5. next 후보지 큐에 등록
    			int next = alis[now][i];
    			q.push(next);
    		}
    	}
}

int main(){
    input();

    bfs(start);

}