#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 100001;
const int LOG = 17; // log2(100,000) ≈ 17

int N, M;
char milkType[MAXN];
vector<int> tree[MAXN];
int depth[MAXN];
int up[MAXN][LOG];
int prefixH[MAXN], prefixG[MAXN];

void dfs(int node, int parent)
{
    depth[node] = depth[parent] + 1;
    up[node][0] = parent;

    // 누적합 계산
    prefixH[node] = prefixH[parent];
    prefixG[node] = prefixG[parent];
    if (milkType[node - 1] == 'H')
        prefixH[node]++;
    if (milkType[node - 1] == 'G')
        prefixG[node]++;

    // LCA용 2^i 부모 채우기
    for (int i = 1; i < LOG; i++)
    {
        up[node][i] = up[up[node][i - 1]][i - 1];
    }

    // 자식 노드 방문
    for (int child : tree[node])
    {
        if (child != parent)
        {
            dfs(child, node);
        }
    }
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);

    // u를 v와 같은 깊이로 올림
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (depth[u] - (1 << i) >= depth[v])
        {
            u = up[u][i];
        }
    }

    if (u == v)
        return u;

    // 공통 조상 찾기
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

bool query(int A, int B, char C)
{
    int ancestor = lca(A, B);

    int totalH = prefixH[A] + prefixH[B] - 2 * prefixH[ancestor];
    int totalG = prefixG[A] + prefixG[B] - 2 * prefixG[ancestor];

    // 루트 조상을 포함한 경로
    if (milkType[ancestor - 1] == 'H')
        totalH++;
    if (milkType[ancestor - 1] == 'G')
        totalG++;

    if (C == 'H')
        return totalH > 0;
    if (C == 'G')
        return totalG > 0;

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    cin >> milkType;

    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    memset(up, 0, sizeof(up));
    depth[0] = -1;

    // DFS로 트리 구성 및 LCA 정보 초기화
    dfs(1, 0);

    string result;
    for (int i = 0; i < M; i++)
    {
        int A, B;
        char C;
        cin >> A >> B >> C;

        if (query(A, B, C))
        {
            result += '1';
        }
        else
        {
            result += '0';
        }
    }

    cout << result << "\n";
    return 0;
}
