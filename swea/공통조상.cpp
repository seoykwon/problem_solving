#include <iostream>
#include <vector>

using namespace std;

struct Node {
    vector<int> children;
    int parents;
    
    // 생성자: Node 객체가 생성될 때 parents 값을 0으로 초기화
    Node() : parents(0) {}
};

int ans, N, M, A, B;
Node* nodes;
vector<int> ancestorA, ancestorB;

void traverse(int idx, vector<int>& ancestor) {
    int parent = nodes[idx].parents;
    if (parent != 0) {
        traverse(parent, ancestor);
    }
    ancestor.push_back(idx);
}

int dfs(int idx) {
    int res = 1;
    for (int child : nodes[idx].children) {
        res += dfs(child);
    }
    return res;
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        cin >> N >> M >> A >> B;
        nodes = new Node[N + 1];
        ancestorA.clear();
        ancestorB.clear();

        for (int i = 0; i < N + 1; i++) {
            nodes[i] = Node();
        }
        for (int i = 0; i < M; i++) {
            int p, c;
            cin >> p >> c;
            nodes[p].children.push_back(c);
            nodes[c].parents = p;
        }

        traverse(A, ancestorA);
        traverse(B, ancestorB);

        for (int i = 0; i < N; i++) {
            if (ancestorA[i] != ancestorB[i]) break;
            ans = ancestorA[i];
        }

        cout << "#" << t << " " << ans << " " << dfs(ans) << '\n';

        delete[] nodes;
    }

    return 0;
}