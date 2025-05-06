// 미생물 처음 투입시 좌상, 우하 너비
// 쿼리마다 개체수 크기 업뎃 -> cnt 배열로 사라지는 애 처리
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <cstring>

using namespace std;

const int MAXm = 55;
const int MAX = 20;
int arr[MAX][MAX];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
int IDCnt;
int N, Q;
// 좌상, 우하, 번호, 개체수
struct microbe
{
    set<pair<int, int>> pos;
    bool survived = false;
} mic[MAXm];

struct pair_hash
{
    size_t operator()(const pair<int, int> &p) const
    {
        return hash<int>()(p.first) ^ hash<int>()(p.second << 1);
    }
};

int bfs(int sr, int sc, int num)
{
    queue<pair<int, int>> q;
    int used[N][N];
    memset(used, 0, sizeof(used)); // 방문 여부
    used[sr][sc] = 1;
    int cnt = 1;
    q.push({sr, sc});

    while (!q.empty())
    {
        int pr = q.front().first;
        int pc = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int nr = pr + dr[i];
            int nc = pc + dc[i];
            if (nr < 0 || nc < 0 || nr >= N || nc >= N)
                continue;
            if (used[nr][nc] == 1 || arr[nr][nc] != num)
                continue;
            used[nr][nc] = 1;
            q.push({nr, nc});
            cnt += 1;
        }
    }
    return cnt;
}
void into()
{
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    unordered_set<int> us;
    // 지워지는 애 활용 가능성?
    // 개체마다 모든 좌표 다 가지고 있기?
    for (int r = r1; r < r2; ++r)
    {
        for (int c = c1; c < c2; ++c)
        {
            if (arr[r][c] != 0)
            {
                if (us.find(arr[r][c]) == us.end())
                {
                    us.insert(arr[r][c]);
                }
                mic[arr[r][c]].pos.erase({r, c}); // 지우기
            }
            mic[IDCnt].pos.insert({r, c}); // 넣기
            arr[r][c] = IDCnt;
        }
    }
    for (auto it : us)
    {
        auto it2 = mic[it].pos.begin();
        auto [mr, mc] = *it2;
        if (bfs(mr, mc, it) != mic[it].pos.size())
        {
            for (auto it3 = it2; it3 != mic[it].pos.end(); ++it3)
            {
                arr[it3->first][it3->second] = 0;
            }
            mic[it].survived = false;
        }
    }
}
int check_move(int new_arr[MAX][MAX], int r, int c, int cur)
{
    auto it2 = mic[cur].pos.begin();
    auto [hr, hc] = *it2;
    for (auto it = mic[cur].pos.begin(); it != mic[cur].pos.end(); ++it)
    {
        auto [nr, nc] = *it;
        nr += r - hr;
        nc += c - hc;
        if (nr < 0 || nc < 0 || nr >= N || nc >= N || new_arr[nr][nc] != 0)
        {
            return 0;
        }
    }
    return 1;
}
void move(int &cnt)
{
    int new_arr[MAX][MAX];
    memset(new_arr, 0, sizeof(new_arr));
    unordered_set<pair<int, int>, pair_hash> us;

    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b)
    {
        if (a.first == b.first)
            return a.second < b.second;
        return a.first > b.first;
    };

    set<pair<int, int>, decltype(cmp)> s(cmp);

    for (int i = 1; i <= IDCnt; ++i)
    {
        if (!mic[i].survived)
            continue;
        s.insert({mic[i].pos.size(), i});
    }
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        int flag = 0;
        for (int r = 0; r < N; ++r)
        {
            for (int c = 0; c < N; ++c)
            {
                flag = check_move(new_arr, r, c, it->second);
                if (flag == 1)
                {
                    vector<pair<int, int>> to_insert;
                    auto it2 = mic[it->second].pos.begin();
                    auto [hr, hc] = *it2;
                    for (auto it3 = mic[it->second].pos.begin(); it3 != mic[it->second].pos.end(); ++it3)
                    {
                        auto [nr, nc] = *it3;
                        nr += r - hr;
                        nc += c - hc;
                        to_insert.emplace_back(nr, nc);
                        new_arr[nr][nc] = it->second;
                        for (int i = 0; i < 4; ++i)
                        {
                            int nnr = nr + dr[i];
                            int nnc = nc + dc[i];
                            if (nnr < 0 || nnc < 0 || nnr >= N || nnc >= N)
                                continue; // 벽이면 pass
                            if (new_arr[nnr][nnc] == it->second or new_arr[nnr][nnc] == 0)
                                continue; // 같은 애면 pass
                            pair<int, int> tp = {min(it->second, new_arr[nnr][nnc]), max(it->second, new_arr[nnr][nnc])};
                            if (us.find(tp) == us.end())
                            {
                                us.insert(tp);
                                cnt += mic[it->second].pos.size() * mic[new_arr[nnr][nnc]].pos.size();
                            }
                        }
                    }
                    mic[it->second].pos.clear();
                    for (const auto &p : to_insert)
                    {
                        mic[it->second].pos.insert(p);
                    }
                    break;
                }
            }
            if (flag == 1)
                break;
        }
        if (flag == 0)
        {
            mic[it->second].survived = false; // 이동 불가
        }
    }

    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            arr[r][c] = new_arr[r][c];
        }
    }
}
int main()
{
    cin >> N >> Q; // N: 미생물 크기, Q: 쿼리 수
    IDCnt = 1;
    for (int q = 0; q < Q; ++q)
    {
        int result = 0;
        into();
        IDCnt++;
        mic[q + 1].survived = true;
        // for(int i = 1; i <= IDCnt; ++i) {
        //     cout << mic[i].pos.size() << '\n'; // 확인용
        // }
        // for(int i = 0; i < N; ++i) {
        //     for (int j = 0; j < N; ++j) {
        //         cout << arr[i][j] << ' ';
        //     }
        //     cout << '\n';
        // }
        move(result);
        // for(int i = 0; i < N; ++i) {
        //     for (int j = 0; j < N; ++j) {
        //         cout << arr[i][j] << ' ';
        //     }
        //     cout << '\n';
        // }
        cout << result << '\n'; // 쿼리마다 출력
    }
    return 0;
}
