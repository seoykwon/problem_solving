#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_N 15
#define MAX_Q 50

#define BLANK 0

using namespace std;

struct loc
{
    int x, y;
};

struct microInfo
{
    int x, y;
    int h, w;
    bool dead;
    bool shape[MAX_N][MAX_N];
    int area;
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int n, q;
vector<vector<int>> board(MAX_N, vector<int>(MAX_N, 0));
vector<vector<int>> newBoard(MAX_N, vector<int>(MAX_N, 0));
microInfo m[51];

void printBoard()
{
    cout << "\n===board===\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << "\n";
    }
    return;
}

void printM(int t)
{
    for (int i = 1; i <= t; i++)
    {
        microInfo curr = m[i];

        if (curr.dead)
            continue;

        printf("x: %d, y: %d, h: %d, w: %d\n", curr.x, curr.y, curr.h, curr.w);

        for (int x = 0; x < curr.h; x++)
        {
            for (int y = 0; y < curr.w; y++)
            {
                if (!curr.shape[x][y])
                    cout << ' ' << ' ';
                else
                    cout << i << ' ';
            }
            cout << "\n";
        }
    }
    return;
}

int bfs(int startX, int startY, int mNum)
{
    microInfo target = m[mNum];

    int area = 0;
    queue<loc> q;
    vector<vector<bool>> visited(MAX_N, vector<bool>(MAX_N, false));

    q.push({startX, startY});
    visited[startX][startY] = true;
    area++;

    while (!q.empty())
    {
        loc curr = q.front();
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            loc nxt = {curr.x + dx[d], curr.y + dy[d]};

            if (nxt.x < 0 || nxt.x >= target.h || nxt.y < 0 || nxt.y >= target.w)
                continue;
            if (!target.shape[nxt.x][nxt.y])
                continue;
            if (visited[nxt.x][nxt.y])
                continue;

            q.push(nxt);
            visited[nxt.x][nxt.y] = true;
            area++;
        }
    }
    return area;
}

bool isSplit(int mNum)
{
    microInfo curr = m[mNum];

    int area = 0;
    for (int i = 0; i < curr.h; i++)
    {
        for (int j = 0; j < curr.w; j++)
        {
            if (curr.shape[i][j])
            {
                area = bfs(i, j, mNum);
                break;
            }
        }
    }

    if (m[mNum].area != area)
        return true;
    return false;
}

bool isFit(int targetX, int targetY, int idx)
{
    microInfo curr = m[idx];

    for (int i = 0; i < curr.h; i++)
    {
        for (int j = 0; j < curr.w; j++)
        {
            if (!curr.shape[i][j])
                continue;

            int x = targetX + i;
            int y = targetY + j;

            if (x < 0 || x >= n || y < 0 || y >= n)
                return false;

            if (board[x][y] != BLANK)
                return false;
        }
    }
    return true;
}

void paintMicro(int idx)
{
    microInfo target = m[idx];

    for (int i = 0; i < target.h; i++)
    {
        for (int j = 0; j < target.w; j++)
        {
            if (!target.shape[i][j])
                continue;
            board[target.x + i][target.y + j] = idx;
        }
    }
    return;
}

bool isNeighbor(int aIdx, int bIdx)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != aIdx)
                continue;

            for (int d = 0; d < 4; d++)
            {
                loc nxt = {i + dx[d], j + dy[d]};

                if (nxt.x < 0 || nxt.x >= n || nxt.y < 0 || nxt.y >= n)
                    continue;
                if (board[nxt.x][nxt.y] == bIdx)
                    return true;
            }
        }
    }
    return false;
}

vector<int> solve()
{
    vector<int> ans;

    for (int t = 1; t <= q; t++)
    {
        // 1. 미생물 투입
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        // m[t]에 미생물 정보 저장
        m[t] = {r1, c1, (r2 - r1), (c2 - c1), false};
        for (int i = 0; i < m[t].h; i++)
        {
            for (int j = 0; j < m[t].w; j++)
            {
                m[t].shape[i][j] = true;
            }
        }
        m[t].area = m[t].h * m[t].w;

        // 보드에 기록
        for (int i = 0; i < m[t].h; i++)
        {
            for (int j = 0; j < m[t].w; j++)
            {
                int currX = m[t].x + i, currY = m[t].y + j;
                // 미생물 이미 존재하는 칸
                if (board[currX][currY] != BLANK)
                {
                    int num = board[currX][currY];
                    m[num].shape[currX - m[num].x][currY - m[num].y] = false;
                    m[num].area--;
                }
                board[currX][currY] = t;
            }
        }

        // 폐기할 미생물 체크
        for (int idx = 1; idx < t; idx++)
        {
            // 폐기 x
            if (m[idx].area > 0 && !isSplit(idx))
                continue;

            // 폐기 o
            m[idx].dead = true;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (board[i][j] == idx)
                    {
                        board[i][j] = BLANK;
                    }
                }
            }
        }

        // 2. 배양 용기 이동
        vector<pair<int, int>> v;
        for (int idx = 1; idx <= t; idx++)
        {
            if (m[idx].dead)
                continue;
            v.push_back({-m[idx].area, idx});
        }
        sort(v.begin(), v.end());

        board = newBoard;

        for (pair<int, int> curr : v)
        {
            int idx = curr.second;

            bool flag = false;
            for (int i = -m[idx].h; i < n; i++)
            {
                if (flag)
                    break;

                for (int j = -m[idx].w; j < n; j++)
                {
                    if (isFit(i, j, idx))
                    {
                        m[idx].x = i;
                        m[idx].y = j;

                        paintMicro(idx);

                        flag = true;
                        break;
                    }
                }
            }
            if (!flag)
            {
                m[idx].dead = true;
            }
        }

        // 3. 실험결과 기록
        int res = 0;

        for (int aIdx = 1; aIdx <= t; aIdx++)
        {
            for (int bIdx = aIdx + 1; bIdx <= t; bIdx++)
            {
                if (isNeighbor(aIdx, bIdx))
                    res += m[aIdx].area * m[bIdx].area;
            }
        }
        ans.push_back(res);
    }
    return ans;
}

int main()
{
    cin >> n >> q;

    vector<int> ans = solve();

    for (int res : ans)
    {
        cout << res << '\n';
    }

    return 0;
}