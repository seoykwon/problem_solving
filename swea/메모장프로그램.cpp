#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_INSERT 200
#define CMD_MOVECURSOR 300
#define CMD_COUNT 400

extern void init(int H, int W, char mStr[]);
extern void insert(char mChar);
extern char moveCursor(int mRow, int mCol);
extern int countCharacter(char mChar);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run()
{
    bool correct = false;
    int queryCnt;
    scanf("%d", &queryCnt);
    int H, W;
    char mChar;
    static char mStr[90001];

    while (queryCnt--)
    {
        int cmd;
        scanf("%d", &cmd);

        if (cmd == CMD_INIT)
        {
            scanf("%d %d %s", &H, &W, mStr);
            init(H, W, mStr);
            correct = true;
        }
        else if (cmd == CMD_INSERT)
        {
            scanf(" %c", &mChar);
            insert(mChar);
        }
        else if (cmd == CMD_MOVECURSOR)
        {
            int mRow, mCol;
            scanf("%d %d", &mRow, &mCol);

            char ret = moveCursor(mRow, mCol);

            char ans;
            scanf(" %c", &ans);
            if (ret != ans)
            {
                correct = false;
            }
        }
        else if (cmd == CMD_COUNT)
        {
            scanf(" %c", &mChar);

            int ret = countCharacter(mChar);

            int ans;
            scanf("%d", &ans);
            if (ret != ans)
            {
                correct = false;
            }
        }
    }
    return correct;
}

int main()
{
    setbuf(stdout, NULL);
    // freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

deque<char> grid[303];
int counting[303][26];
int h, w;
int cur_r, cur_c;
int len;

void init(int H, int W, char str[])
{
    len = 0;
    h = H, w = W;
    memset(counting, 0, sizeof(counting));
    for (int i = 0; i < 303; ++i)
        grid[i].clear();
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (str[len])
            {
                counting[i][str[len] - 'a']++;
                grid[i].push_back(str[len++]);
            }
            else
                break;
        }
    }
    cur_r = cur_c = 0;
}

void insert(char c)
{
    grid[cur_r].insert(grid[cur_r].begin() + cur_c, c);
    counting[cur_r][c - 'a']++;
    int row = cur_r;
    ++cur_c;
    ++len;
    if (cur_c == w)
    {
        ++cur_r;
        cur_c = 0;
    }
    while ((int)grid[row].size() > w)
    {
        char bk = grid[row].back();

        counting[row][bk - 'a']--;
        grid[row].pop_back();

        counting[row + 1][bk - 'a']++;
        grid[row + 1].push_front(bk);
        ++row;
    }
}

char moveCursor(int row, int col)
{
    --row, --col;
    if (row * w + col >= len)
    {
        row = len / w;
        col = len % w;
        cur_r = row, cur_c = col;
        return '$';
    }
    cur_r = row, cur_c = col;
    return grid[row][col];
}

int countCharacter(char c)
{
    int row = cur_r, col = cur_c;
    int ret = 0;
    if (col)
    {
        for (int i = col; i < (int)grid[row].size(); ++i)
        {
            ret += grid[row][i] == c;
        }
        ++row;
    }
    for (int i = row; i < h; ++i)
    {
        ret += counting[i][c - 'a'];
    }
    return ret;
}
