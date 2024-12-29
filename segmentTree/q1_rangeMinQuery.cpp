#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

vector<int> arr;      // 입력 배열
vector<int> seg_tree; // 세그먼트 트리

// 세그먼트 트리 빌드 함수
int build_tree(int node, int start, int end)
{
    if (start == end)
    {
        // 리프 노드: 배열의 원소를 저장
        return seg_tree[node] = arr[start];
    }

    int mid = (start + end) / 2;
    // 왼쪽 자식과 오른쪽 자식을 재귀적으로 빌드
    int left_min = build_tree(2 * node, start, mid);
    int right_min = build_tree(2 * node + 1, mid + 1, end);

    // 현재 노드는 두 자식의 최솟값
    return seg_tree[node] = min(left_min, right_min);
}

// 구간 최소값 쿼리 함수
int query(int node, int start, int end, int left, int right)
{
    if (right < start || end < left)
    {
        // 구간이 겹치지 않음 -> 무한대 반환
        return INT_MAX;
    }

    if (left <= start && end <= right)
    {
        // 구간이 완전히 포함됨
        return seg_tree[node];
    }

    // 구간이 부분적으로 겹침 -> 자식 노드에서 탐색
    int mid = (start + end) / 2;
    int left_min = query(2 * node, start, mid, left, right);
    int right_min = query(2 * node + 1, mid + 1, end, left, right);

    // 두 자식 노드의 최솟값 반환
    return min(left_min, right_min);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    arr.resize(N);
    int tree_height = (int)ceil(log2(N));
    int tree_size = (1 << (tree_height + 1)); // 세그먼트 트리 배열 크기
    seg_tree.resize(tree_size);

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    // 세그먼트 트리 빌드
    build_tree(1, 0, N - 1);

    while (M--)
    {
        int s, e;
        cin >> s >> e;

        // s, e는 1-based 인덱스이므로, 0-based로 변환
        cout << query(1, 0, N - 1, s - 1, e - 1) << '\n';
    }

    return 0;
}
