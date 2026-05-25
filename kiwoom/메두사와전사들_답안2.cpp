#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<vector<int>> arr;
vector<array<int,2>> men;

//                  상,우상, 우,우하, 하,좌하, 좌,좌상
//                   0,  1,  2,  3,  4,  5,  6,  7
const int di8[] = {-1, -1, 0, 1, 1,  1,  0, -1};
const int dj8[] = { 0,  1, 1, 1, 0, -1, -1, -1};

// BFS로 메두사 최단경로 찾기 (도로 따라, 상하좌우 우선순위)
vector<pair<int,int>> find_route(int si, int sj, int ei, int ej, bool &found) {
    vector<vector<pair<int,int>>> v(N, vector<pair<int,int>>(N, {-1, -1}));
    queue<pair<int,int>> q;
    q.push({si, sj});
    v[si][sj] = {si, sj};   // 직전위치 저장 (start는 자기자신)

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = { 0, 0, -1, 1};

    while (!q.empty()) {
        auto [ci, cj] = q.front();
        q.pop();

        if (ci == ei && cj == ej) {
            found = true;
            vector<pair<int,int>> route;
            int pi = v[ci][cj].first, pj = v[ci][cj].second;
            while (!(pi == si && pj == sj)) {   // 출발지가 아니라면 저장
                route.push_back({pi, pj});
                int npi = v[pi][pj].first, npj = v[pi][pj].second;
                pi = npi; pj = npj;
            }
            reverse(route.begin(), route.end());    // 메두사 이동순서대로
            return route;
        }

        for (int k = 0; k < 4; k++) {
            int ni = ci + dx[k], nj = cj + dy[k];
            if (0 <= ni && ni < N && 0 <= nj && nj < N
                && v[ni][nj].first == -1 && arr[ni][nj] == 0) {
                q.push({ni, nj});
                v[ni][nj] = {ci, cj};
            }
        }
    }
    found = false;
    return {};
}

// 시각적 구분 위해 2로 표시(전사에 가려진 영역)
void mark_line(vector<vector<int>> &v, int ci, int cj, int dr) {
    while (0 <= ci && ci < N && 0 <= cj && cj < N) {
        v[ci][cj] = 2;
        ci += di8[dr];
        cj += dj8[dr];
    }
}

void mark_safe(vector<vector<int>> &v, int si, int sj, int dr, int org_dr) {
    // [1] 직선방향 표시
    int ci = si + di8[dr], cj = sj + dj8[dr];
    mark_line(v, ci, cj, dr);

    // [2] 바라보는 방향으로 한줄씩 표시
    ci = si + di8[org_dr];
    cj = sj + dj8[org_dr];
    while (0 <= ci && ci < N && 0 <= cj && cj < N) {
        mark_line(v, ci, cj, dr);
        ci += di8[org_dr];
        cj += dj8[org_dr];
    }
}

// dr 방향에서 돌로 만들 수 있는 전사 수 계산
pair<vector<vector<int>>, int> make_stone(vector<vector<int>> &marr, int mi, int mj, int dr) {
    vector<vector<int>> v(N, vector<int>(N, 0));
    int cnt = 0;

    // [1] dr 방향으로 >0 만날때까지 1표시, 이후좌표 2표시
    {
        int ni = mi + di8[dr], nj = mj + dj8[dr];
        while (0 <= ni && ni < N && 0 <= nj && nj < N) {
            v[ni][nj] = 1;
            if (marr[ni][nj] > 0) {
                cnt += marr[ni][nj];
                ni += di8[dr]; nj += dj8[dr];
                mark_line(v, ni, nj, dr);
                break;
            }
            ni += di8[dr]; nj += dj8[dr];
        }
    }

    // [2] dr-1, dr+1 대각선 방향으로 동일처리 (음수 모듈로 주의!)
    int org_drs[2] = { ((dr - 1) % 8 + 8) % 8, (dr + 1) % 8 };
    for (int org_dr : org_drs) {
        int si = mi + di8[org_dr], sj = mj + dj8[org_dr];   // 첫 대각선 위치
        while (0 <= si && si < N && 0 <= sj && sj < N) {
            // 전사 만나면 전사가 바라보는 방향 처리
            if (v[si][sj] == 0 && marr[si][sj] > 0) {
                v[si][sj] = 1;
                cnt += marr[si][sj];
                mark_safe(v, si, sj, dr, org_dr);
                break;
            }

            // 첫 위치가 전사가 아닌 경우 직선으로 내려오며 탐색
            int ci = si, cj = sj;
            while (0 <= ci && ci < N && 0 <= cj && cj < N) {
                if (v[ci][cj] == 0) {       // 처음 방문
                    v[ci][cj] = 1;
                    if (marr[ci][cj] > 0) { // 전사로 막혔으면
                        cnt += marr[ci][cj];
                        mark_safe(v, ci, cj, dr, org_dr);
                        break;
                    }
                } else {
                    break;
                }
                ci += di8[dr]; cj += dj8[dr];
            }

            si += di8[org_dr]; sj += dj8[org_dr];
        }
    }

    return {v, cnt};
}

// 전사들의 이동 (상하좌우 → 좌우상하 두 번)
pair<int,int> move_men(vector<vector<int>> &v, int mi, int mj) {
    int move_cnt = 0, attk_cnt = 0;

    int dirs[2][4][2] = {
        {{-1,0},{1,0},{0,-1},{0,1}},    // 상하좌우
        {{0,-1},{0,1},{-1,0},{1,0}}     // 좌우상하
    };

    for (int d = 0; d < 2; d++) {
        for (int idx = (int)men.size() - 1; idx >= 0; idx--) {
            int ci = men[idx][0], cj = men[idx][1];
            if (v[ci][cj] == 1) continue;   // 메두사 시야면 얼음!

            int dist = abs(mi - ci) + abs(mj - cj);     // 현재 거리
            for (int k = 0; k < 4; k++) {
                int ddi = dirs[d][k][0], ddj = dirs[d][k][1];
                int ni = ci + ddi, nj = cj + ddj;
                // 범위내, 메두사시야 아니고, 거리가 줄어드는 방향
                if (0 <= ni && ni < N && 0 <= nj && nj < N
                    && v[ni][nj] != 1
                    && dist > abs(mi - ni) + abs(mj - nj)) {
                    if (ni == mi && nj == mj) {
                        attk_cnt++;
                        men.erase(men.begin() + idx);
                    } else {
                        men[idx] = {ni, nj};
                    }
                    move_cnt++;
                    break;
                }
            }
        }
    }
    return {move_cnt, attk_cnt};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    int si, sj, ei, ej;
    cin >> si >> sj >> ei >> ej;

    men.assign(M, {0, 0});
    for (int i = 0; i < M; i++) {
        cin >> men[i][0] >> men[i][1];
    }

    arr.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }

    // [0] BFS로 메두사 최단경로 찾기 (없으면 -1)
    bool found;
    auto route = find_route(si, sj, ei, ej, found);

    if (!found) {
        cout << -1 << "\n";
    } else {
        for (auto [mi, mj] : route) {
            // [1] 메두사 이동: 같은 좌표의 전사 제거 (역순 삭제)
            for (int i = (int)men.size() - 1; i >= 0; i--) {
                if (men[i][0] == mi && men[i][1] == mj) {
                    men.erase(men.begin() + i);
                }
            }

            // [2] 메두사 시선: 상하좌우 중 최대로 돌로 만드는 방향
            vector<vector<int>> marr(N, vector<int>(N, 0));
            for (auto &m : men) marr[m[0]][m[1]]++;

            int mx_stone = -1;
            vector<vector<int>> v;
            for (int dr : {0, 4, 6, 2}) {   // 상하좌우 순서로 처리
                auto [tv, tstone] = make_stone(marr, mi, mj, dr);
                if (mx_stone < tstone) {
                    mx_stone = tstone;
                    v = tv;
                }
            }

            // [3] 전사들의 이동 (한 칸씩 두 번): 메두사 있는 경우 공격
            auto [move_cnt, attk_cnt] = move_men(v, mi, mj);

            cout << move_cnt << " " << mx_stone << " " << attk_cnt << "\n";
        }
        cout << 0 << "\n";
    }

    return 0;
}
