// #include <iostream>
// #include <vector>

// using namespace std;

// int n;
// vector <int> v[1001];
// int visited[1001];

// void input(){
//     cin >> n;

//     for(int i = 0; i < n; i++){
//         int parent, c1, c2;

//         cin >> parent >> c1 >> c2;

//         v[parent].push_back(c1);
//         v[parent].push_back(c2);
//         v[c1].push_back(parent);
//         v[c2].push_back(parent);
//     }

// }

// void dfs1(int now){
//     visited[now] = 1;

//     for(int next: v[now]){
//         if(!visited[next]){
//             dfs1(next);
//             cout << next << " ";
//             visited[next] = 0;
//         }
//     }
// }

// void dfs2(int now){}

// void dfs3(int now){}

// int main(){
    
//     input();

//     dfs1(0);
// }

// #include <iostream>
// #include <vector>
// #include <map>

// using namespace std;

// map<int, pair<int, int>> tree; // 트리 구성: 노드 번호 -> (왼쪽 자식, 오른쪽 자식)

// // 중위 순회 (Inorder Traversal)
// void inorder(int node, vector<int>& result) {
//     if (node == -1) return;
//     inorder(tree[node].first, result);
//     result.push_back(node);
//     inorder(tree[node].second, result);
// }

// // 전위 순회 (Preorder Traversal)
// void preorder(int node, vector<int>& result) {
//     if (node == -1) return;
//     result.push_back(node);
//     preorder(tree[node].first, result);
//     preorder(tree[node].second, result);
// }

// // 후위 순회 (Postorder Traversal)
// void postorder(int node, vector<int>& result) {
//     if (node == -1) return;
//     postorder(tree[node].first, result);
//     postorder(tree[node].second, result);
//     result.push_back(node);
// }

// int main() {
//     int N;
//     cin >> N;

//     for (int i = 0; i < N; ++i) {
//         int node, left, right;
//         cin >> node >> left >> right;
//         tree[node] = {left, right};
//     }

//     vector<int> inorder_result;
//     vector<int> preorder_result;
//     vector<int> postorder_result;

//     // 루트 노드는 항상 1로 가정
//     int root = 1;

//     // 각 순회 방식으로 탐색 수행
//     inorder(root, inorder_result);
//     preorder(root, preorder_result);
//     postorder(root, postorder_result);

//     // 중위 순회 결과 출력
//     for (int i = 0; i < inorder_result.size(); ++i) {
//         if (i > 0) cout << " ";
//         cout << inorder_result[i];
//     }
//     cout << endl;

//     // 전위 순회 결과 출력
//     for (int i = 0; i < preorder_result.size(); ++i) {
//         if (i > 0) cout << " ";
//         cout << preorder_result[i];
//     }
//     cout << endl;

//     // 후위 순회 결과 출력
//     for (int i = 0; i < postorder_result.size(); ++i) {
//         if (i > 0) cout << " ";
//         cout << postorder_result[i];
//     }
//     cout << endl;

//     return 0;
// }


#include <iostream>
#include <vector>
using namespace std;

int tree[1001][2]; 
int N;
vector<int>preorder;
vector<int>inorder;
vector<int>postorder; 

void dfs(int now) {

	if (now == -1)
		return;
	preorder.push_back(now);
	
	// 왼쪽으로 탐색 
	dfs(tree[now][0]);
	inorder.push_back(now);
	
	// 오른쪽으로 탐색
	dfs(tree[now][1]);
	postorder.push_back(now);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int root, left, right; 
		cin >> root >> left >> right;
		// root의 왼쪽 
		tree[root][0] = left;
		// root의 오른쪽
		tree[root][1] = right; 
	}

	dfs(1);

	for (auto it = inorder.begin(); it != inorder.end(); it++) 
		cout << *it << " ";
	cout << '\n';
	for (auto it = preorder.begin(); it != preorder.end(); it++)
		cout << *it << " ";
	cout << '\n';
	for (auto it = postorder.begin(); it != postorder.end(); it++)
		cout << *it << " ";
}