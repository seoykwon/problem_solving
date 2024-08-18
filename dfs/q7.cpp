#include <iostream>
#include <vector>

using namespace std;

int n, m, target;

vector <int> upv[100001];
vector <int> downv[100001];

int up = 1;
int down = 1;

int upused[100001];
int downused[100001];

void updfs(int node) {
    for (int i = 0; i < upv[node].size(); i++){
        int next = upv[node][i];
        if (upused[next] == 1) continue;
        up++;
        upused[next] = 1;
        updfs(next);
    }
}

void downdfs(int node){
    for (int i = 0; i < downv[node].size(); i++){
        int next = downv[node][i];
        if (downused[next] == 1) continue;
        down++;
        downused[next] = 1;
        downdfs(next);
    }
}

int main() {
    cin >> n >> m >> target;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        upv[b].push_back(a);
        upv[a].push_back(b);
    }

    updfs(target);
    downdfs(target);
    cout << up << endl;
    cout << n - down + 1;
}