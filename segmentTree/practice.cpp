#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;   // 값의 합이 int 범위 넘을 수 있어서 long long 사용

vector<ll> segTree;     // 세그먼트 트리 본체. 1-based. 노드 i의 자식은 2i, 2i+1
vector<ll> numV;        // 원본 배열 (1-based로 쓰기 위해 인덱스 0에 더미 0 push)
int N, M, K;            // N: 수의 개수, M: 변경 횟수, K: 구간합 횟수

// ─────────────────────────────────────────────────────────────
// init: 세그먼트 트리 구축
//   [start, end] : 현재 node가 담당하는 "원본 배열 구간"
//   node         : 세그먼트 트리 배열에서의 현재 위치(인덱스)
//   반환값       : 이 구간의 합 (재귀적으로 부모에게 전달됨)
// ─────────────────────────────────────────────────────────────
ll init(int start, int end, int node) {
    // [Base case] 구간 길이가 1 → 리프 노드
    // 이 노드는 원본 배열의 start번 원소 하나만 담당
    if (start == end)
        return segTree[node] = numV[start];

    int mid = (start + end) >> 1;   // (start+end)/2. 비트시프트는 그냥 빠른 나누기 2
    // 왼쪽 자식: [start, mid] 담당, 트리 인덱스는 node*2
    // 오른쪽 자식: [mid+1, end] 담당, 트리 인덱스는 node*2+1
    // 내 값 = 왼쪽 자식 값 + 오른쪽 자식 값 (post-order로 채워짐)
    return segTree[node] = init(start, mid, node << 1)
                         + init(mid + 1, end, (node << 1) + 1);
}

// ─────────────────────────────────────────────────────────────
// sum: 구간 [left, right]의 합을 구함
//   [start, end] : 현재 node가 담당하는 구간 (트리를 따라 내려가며 변함)
//   [left, right]: 우리가 알고 싶은 쿼리 구간 (재귀 내내 고정)
// ─────────────────────────────────────────────────────────────
ll sum(int start, int end, int left, int right, int node) {
    // [Case 1] 내 담당 구간이 쿼리 구간과 완전히 겹치지 않음 → 기여 없음
    // (덧셈의 항등원인 0 반환. min 쿼리였다면 INF였을 자리)
    if (left > end || right < start)
        return 0;

    // [Case 2] 내 담당 구간이 쿼리 구간에 완전히 포함됨 → 저장된 값 그대로 반환
    // 핵심 최적화 포인트: 더 내려갈 필요 없이 이미 계산된 합을 씀
    if (left <= start && right >= end)
        return segTree[node];

    // [Case 3] 부분적으로 걸침 → 반으로 쪼개 양쪽에 물어봄
    int mid = (start + end) >> 1;
    return sum(start, mid, left, right, node << 1)
         + sum(mid + 1, end, left, right, (node << 1) + 1);
}

// ─────────────────────────────────────────────────────────────
// update: 원본의 target 위치 값에 diff만큼 변화가 생겼을 때 트리 갱신
//   diff: "바뀐 양" (새값 - 옛값). 차이만 더해주는 게 핵심 트릭
//   target 위치를 포함하는 모든 조상 노드들의 합이 diff만큼 늘어남
// ─────────────────────────────────────────────────────────────
void update(int start, int end, int target, ll diff, int node) {
    // target이 내 담당 구간 밖이면 나는 영향 없음 → 그냥 종료
    if (target > end || target < start)
        return;

    // 내 담당 구간이 target을 포함 → 내 합도 diff만큼 변동
    segTree[node] += diff;

    // 리프면 끝. 자식 없음
    if (start == end)
        return;

    // 두 자식 모두 재귀 호출 (실제로는 둘 중 하나만 target을 품지만,
    //   두 번째 줄의 가드(target > end || target < start)가 다른 쪽을 즉시 컷오프함)
    int mid = (start + end) >> 1;
    update(start, mid, target, diff, node << 1);
    update(mid + 1, end, target, diff, (node << 1) + 1);
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);   // C++ 입출력 가속 (cin/cout 빠르게)

    cin >> N >> M >> K;

    // 세그먼트 트리 배열 크기 계산:
    //   N개 리프를 담을 수 있는 가장 작은 2의 거듭제곱 ≥ N
    //   트리는 이 리프 수의 2배 정도 필요 → 2^(⌈log2(N)⌉ + 1)
    //   (실무에선 그냥 4*N으로 잡는 게 흔하고 안전함)
    int h = ceil(log2(N));
    int treeSize = 1 << (h + 1);    // 2^(h+1)
    segTree = vector<ll>(treeSize); // 0으로 초기화

    numV.push_back(0);              // 1-based 인덱싱을 위해 0번 자리에 더미

    for (int i = 0; i < N; i++) {
        ll num;
        cin >> num;
        numV.push_back(num);        // numV[1] ~ numV[N]에 원본 값 저장
    }

    init(1, N, 1);                  // 루트(=1번 노드)부터 [1, N] 구간으로 트리 구축

    // 쿼리 처리: 변경 M번 + 구간합 K번 (총 M+K개, 순서 섞여서 들어옴)
    for (int i = 0; i < M + K; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;

        if (a == 1) {
            // 변경 쿼리: b번 원소를 c로 바꿔라
            ll diff = c - numV[b];  // 변화량 계산
            numV[b] = c;            // 원본 배열 갱신
            update(1, N, b, diff, 1);   // 트리에 변화량 전파
        } else {
            // 합 쿼리 (a == 2): [b, c] 구간 합 출력
            cout << sum(1, N, b, c, 1) << "\n";
        }
    }
    return 0;
}