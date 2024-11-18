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