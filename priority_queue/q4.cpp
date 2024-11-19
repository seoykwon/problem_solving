#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
using pll = pair<ll, ll>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // 입력을 받은 후 시계열순 정렬
    int N;
    cin >> N;
    vector<vector<int>> v;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        v.push_back({a, b, i});
    }
    sort(v.begin(), v.end());

    priority_queue<vector<int>> q;
    int nxt = v[0][0], idx = 0, ans = 0; // nxt = 다음으로 프린터를 쓸 수 있는 시간, idx = 현재 보고 있는 쿼리 인덱스, ans = 답
    // 스위핑
    while (idx < N)
    {
        // 사용 가능한 시간까지, 들어온 쿼리는 pq에 삽입 또는 pq가 비어있을 때는 바로 삽입
        // 우선순위를 음수로 하고 맨 앞에 넣으면 알아서 정렬됨
        while (q.empty() || (idx < N && nxt >= v[idx][0]))
        {
            q.push({-v[idx][2], v[idx][0], v[idx][1]});
            idx++;
        }
        // 현재 쿼리
        auto cur = q.top();
        int num = -cur[0], st = cur[1], dt = cur[2];
        nxt = max(st, nxt); // 결과적으로 시작하게 되는 시간은 프린터 사용 가능한 시점과 원 쿼리가 주어진 시점 중 큰 값
        q.pop();

        ans = max(ans, nxt - st); // 기다린 시간에 대한 답 갱신 처리
        nxt += dt;                // 다음 프린터 사용 가능 시간 갱신
    }
    cout << ans;
}