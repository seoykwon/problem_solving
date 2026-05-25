#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;

const int MAX_N = 50;

struct Board {
    bool is_amcho = false;
    bool visit = false;
} boards[MAX_N + 1][MAX_N + 1];

struct Whale {
    pii pos;
    int dir;        // udlr
} whale;

int N;

void Input() {
    cin >> N >> whale.pos.first >> whale.pos.second >> whale.dir;
    whale.dir--;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> boards[i][j].is_amcho;
        }
    }
}

bool isOutOfMap(pii pos) {
    return pos.first <= 0 || pos.first > N || pos.second <= 0 || pos.second > N;
}


pii operator+(const pii& a, const pii& b) {
    return { a.first + b.first, a.second + b.second };
}
pii operator-(const pii& a, const pii& b) {
    return { a.first - b.first, a.second - b.second };
}
bool operator==(const pii& a, const pii& b) {
    return a.first == b.first && a.second == b.second;
}

pii udlr[4] = { {-1, 0}, {1, 0}, {0,-1}, {0, 1} };
bool canDoStep1() {
    for (int i = 0; i < 4; i++) {
        pii next_pos = whale.pos + udlr[i];
        if (isOutOfMap(next_pos) || boards[next_pos.first][next_pos.second].is_amcho || boards[next_pos.first][next_pos.second].visit) continue;
        return true;
    }
    return false;
}

pii doStep1() {
    pii step1_ulrd[4][4] = {    // udlr -> ulrd
        { {-1, 0}, {0, -1}, {0, +1}, {+1, 0} },
        { {+1, 0}, {0, +1}, {0, -1}, {-1, 0} },
        { {0, -1}, {+1, 0}, {-1, 0}, {0, +1} },
        { {0, +1}, {-1, 0}, {+1, 0}, {0, -1} },
    };
    int step1_dir[4][4] = {
        {0, 2, 3, 1},
        {1, 3, 2, 0},
        {2, 1, 0, 3},
        {3, 0, 1, 2}
    };

    for (int i = 0; i < 4; i++) {
        pii delta = step1_ulrd[whale.dir][i];
        pii next_pos = whale.pos + delta;
        if (isOutOfMap(next_pos) || boards[next_pos.first][next_pos.second].is_amcho || boards[next_pos.first][next_pos.second].visit) continue;
        int next_dir = step1_dir[whale.dir][i];

        whale.pos = next_pos;
        whale.dir = next_dir;
        boards[whale.pos.first][whale.pos.second].visit = true;

        return whale.pos;
    }
}


//int DFS(pii pos, pii& dest) {
//    for (int i = 0; i < 4; i++) {
//        pii next_pos = ldru[i] + pos;
//        if (isOutOfMap(next_pos) || boards[next_pos.first][next_pos.second].is_amcho) continue;
//        if (dist[next_pos.first][next_pos.second] != dist[pos.first][pos.second] + 1) continue;
//        if (next_pos == dest) return i;
//        int ret = DFS(next_pos, dest);
//        if (ret != -1) return ret;
//    }
//    return -1;
//}

pii doStep2() {
    pii ldru[4] = { {0, -1}, {+1, 0}, {0, +1}, {-1, 0} };

    int dist[MAX_N + 1][MAX_N + 1];
    memset(dist, -1, sizeof(dist));

    queue<pii> que;
    que.push(whale.pos);
    dist[whale.pos.first][whale.pos.second] = 0;

    pii min_pos = { -1, -1 };

    while (!que.empty()) {
        pii u = que.front();
        que.pop();

        if (min_pos != make_pair(- 1, -1 )) {
            if (dist[u.first][u.second] == dist[min_pos.first][min_pos.second]) continue;
        }

        for (int i = 0; i < 4; i++) {
            pii v = u + ldru[i];
            if (isOutOfMap(v) || dist[v.first][v.second] != -1 || boards[v.first][v.second].is_amcho) continue;

            dist[v.first][v.second] = dist[u.first][u.second] + 1;

            if (min_pos != make_pair(-1, -1)) {
                if (dist[v.first][v.second] > dist[min_pos.first][min_pos.second]) break;
            }

            if (boards[v.first][v.second].visit) {
                que.push(v);
            }
            else {
                if (min_pos == make_pair(-1, -1)) {
                    min_pos = v;
                }
                else if (v.first < min_pos.first || (v.first == min_pos.first && v.second < min_pos.second)) {
                    min_pos = v;
                }
            }
        }
    }

    if (min_pos == make_pair(-1, -1)) return { -1, -1 };

    // 목적지가 정해지고, 방향 구하기
    int dir_mod[4] = {2, 1, 3, 0};
    whale.pos = min_pos;
    for (int i = 0; i < 4; i++) {
        pii prior_pos = min_pos - ldru[i];
        if (dist[prior_pos.first][prior_pos.second] + 1 == dist[min_pos.first][min_pos.second]) {
            whale.dir = dir_mod[i];
        }
    }
    boards[whale.pos.first][whale.pos.second].visit = true;

    return whale.pos;
}

int cnt = 0;
pii ans[MAX_N * MAX_N];
void Process() {
    ans[cnt++] = whale.pos;
    boards[whale.pos.first][whale.pos.second].visit = true;

    pii moved_pos;
    while (true) {
        if (canDoStep1()) moved_pos = doStep1();
        else moved_pos = doStep2();

        if (moved_pos == make_pair(-1, -1)) break;

        ans[cnt++] = moved_pos;
    }
}

void Output() {
    for (int i = 0; i < cnt; i++) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Input();
    Process();
    Output();

    return 0;
}

