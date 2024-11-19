#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

// 마을이 연결되어 있는지 확인하는 함수 (BFS 사용)
bool is_connected(const vector<int> &group, const vector<vector<int>> &adj_matrix)
{
    queue<int> q;
    vector<bool> visited(adj_matrix.size(), false);

    q.push(group[0]);
    visited[group[0]] = true;
    int count = 1;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        for (int i = 0; i < adj_matrix.size(); ++i)
        {
            if (adj_matrix[current][i] == 1 && !visited[i] && find(group.begin(), group.end(), i) != group.end())
            {
                visited[i] = true;
                q.push(i);
                count++;
            }
        }
    }

    return count == group.size();
}

// 문제 해결 함수
int solve(int N, const vector<vector<int>> &adj_matrix, const vector<int> &populations)
{
    int total_population = 0;
    for (int p : populations)
        total_population += p;

    int min_diff = INT_MAX;

    // 1부터 N//2까지 마을을 나누는 모든 조합을 시도
    for (int i = 1; i <= N / 2; ++i)
    {
        vector<int> indices(N);
        for (int j = 0; j < i; ++j)
            indices[j] = 1;
        do
        {
            vector<int> group_A, group_B;
            for (int j = 0; j < N; ++j)
            {
                if (indices[j])
                    group_A.push_back(j);
                else
                    group_B.push_back(j);
            }

            // 두 그룹이 각각 연결되어 있는지 확인
            if (is_connected(group_A, adj_matrix) && is_connected(group_B, adj_matrix))
            {
                int pop_A = 0, pop_B = 0;
                for (int a : group_A)
                    pop_A += populations[a];
                for (int b : group_B)
                    pop_B += populations[b];

                int diff = abs(pop_A - pop_B);
                min_diff = min(min_diff, diff);
            }
        } while (prev_permutation(indices.begin(), indices.end()));
    }

    return min_diff;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int T; // 테스트 케이스 수
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;

        vector<vector<int>> adj_matrix(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cin >> adj_matrix[i][j];
            }
        }

        vector<int> populations(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> populations[i];
        }

        // 문제 해결
        int result = solve(N, adj_matrix, populations);

        // 결과 출력
        cout << "#" << t << " " << result << endl;
    }

    return 0;
}

/**
 * 1. 왜 N//2까지만 indices를 만드는가?
마을을 두 그룹으로 나눌 때, 한 그룹의 크기는 최대

N//2이어야만 합니다.
N//2를 초과하는 크기의 그룹을 고려하는 것은 불필요합니다. 그 이유는:

A={1,2},B={3,4}와
A={3,4},B={1,2}는 사실상 동일한 경우입니다.
따라서
𝐴
A의 크기를
𝑁//2
N//2까지만 고려하면 모든 가능한 나누기를 다 다루게 됩니다.
2.
𝑁/2
N/2와
𝑁//2
N//2의 차이
𝑁/2
N/2:

실수형 결과를 반환합니다.
예:
5/2=2.5
5/2=2.5.
𝑁//2
N//2:

정수형 몫을 반환합니다 (버림).
예:
5//2=2
5//2=2.
차이점:
𝑁/2
N/2는 실수 값을 반환하므로 정수형 연산에는 적합하지 않습니다.
𝑁//2
N//2는 마을의 수
N이 항상 정수라는 문제의 성질에 맞게 정수 몫만 반환합니다.
특히, 조합 생성 시 마을 수를 정확히 정수로 나눠야 하므로
𝑁//2
N//2를 사용합니다.

 */