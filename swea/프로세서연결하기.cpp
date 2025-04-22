#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int map[12][12];
vector<pair<int, int>> coreList;
int ans, maxCnt, N;
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};

void input()
{
    cin >> N;
    coreList.clear();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> map[i][j];
            if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
                continue;
            if (map[i][j] == 1)
                coreList.push_back({i, j});
        }
    }
    ans = 0;
    maxCnt = 0;
}

bool inRange(int r, int c)
{
    return 0 <= r && 0 <= c && r < N && c < N;
}

int extend(pair<int, int> point, int d)
{
    int r = point.first + dr[d];
    int c = point.second + dc[d];
    int res = 0;

    while (inRange(r, c))
    {
        if (map[r][c] != 0)
        {
            return -1;
        }
        r += dr[d];
        c += dc[d];
    }
    r = point.first + dr[d];
    c = point.second + dc[d];
    while (inRange(r, c))
    {
        map[r][c] = 2;
        r += dr[d];
        c += dc[d];
        res++;
    }
    return res;
}

void rollback(pair<int, int> point, int d)
{
    int r = point.first + dr[d];
    int c = point.second + dc[d];
    while (inRange(r, c))
    {
        map[r][c] = 0;
        r += dr[d];
        c += dc[d];
    }
}

void backtracking(int idx, int length, int cnt)
{
    if (cnt > maxCnt)
    {
        maxCnt = cnt;
        ans = length;
    }
    else if (cnt == maxCnt)
    {
        ans = min(ans, length);
    }
    if (idx == coreList.size())
    {
        return;
    }

    for (int d = 0; d < 4; d++)
    {
        int nr = coreList[idx].first + dr[d];
        int nc = coreList[idx].second + dc[d];

        int wireLen = extend(coreList[idx], d);
        if (wireLen == -1)
        {
            continue;
        }
        backtracking(idx + 1, length + wireLen, cnt + 1);
        rollback(coreList[idx], d);
    }
    backtracking(idx + 1, length, cnt);
}

void output(int t)
{
    cout << "#" << t << " " << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        input();
        backtracking(0, 0, 0);
        output(t);
    }
    return 0;
}