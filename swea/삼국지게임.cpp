#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_ALLY 300
#define CMD_ATTACK 400
#define CMD_RECRUIT 500

// /////////////////////////////////////////////////////////////////////////
// extern void init(int N, int mSoldier[25][25], char mGeneral[25][25][11]);
// extern void destroy();
// extern int ally(char mMonarchA[11], char mMonarchB[11]);
// extern int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]);
// extern int recruit(char mMonarch[11], int mNum, int mOption);
// /////////////////////////////////////////////////////////////////////////

#define MAX_N 25
#define MAX_L 10

static int Sol[MAX_N][MAX_N];
static char General[MAX_N][MAX_N][MAX_L + 1];

#include <unordered_map>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

int NN;
struct pos
{
    int n;
    int y;
    int x;
};
unordered_map<string, pos> country;
int parent[MAX_N * MAX_N + 1] = {
    0,
};
vector<int> enemy[MAX_N * MAX_N + 1];
vector<pos> allies[MAX_N * MAX_N + 1];
int dir[8][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

int Find(int A)
{
    if (A == parent[A])
    {
        return A;
    }
    return parent[A] = Find(parent[A]);
}

void Union(int A, int B)
{
    int rootA = Find(A);
    int rootB = Find(B);

    if (rootA == rootB)
        return;

    parent[rootB] = parent[rootA];
}

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
    NN = N;
    int cnt = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Sol[i][j] = mSoldier[i][j];
            country.insert({mMonarch[i][j], {cnt, i, j}});
            allies[cnt].push_back({cnt, i, j});
            cnt++;
            for (int k = 0; k < MAX_L; k++)
            {
                if (mMonarch[i][j][k] == '\0')
                    break;
                General[i][j][k] = mMonarch[i][j][k];
            }
        }
    }

    for (int i = 1; i <= N * N; i++)
    {
        parent[i] = i;
    }
}

void destroy()
{
}

int ally(char mMonarchA[11], char mMonarchB[11])
{
    auto itA = country.find(mMonarchA);
    auto itB = country.find(mMonarchB);

    if (itA == country.end() || itB == country.end())
        return -1;

    int aNum = itA->second.n;
    int bNum = itB->second.n;

    int rootA = Find(aNum);
    int rootB = Find(bNum);

    if (rootA == rootB)
        return -1;

    // enemy check
    int eszA = enemy[aNum].size();
    int eszB = enemy[bNum].size();
    if (eszA > 0)
    {
        for (int i = 0; i < eszA; i++)
        {
            int enem = enemy[aNum][i];
            int rootE = Find(enem);

            if (rootB == rootE)
                return -2;
        }
    }

    if (eszB > 0)
    {
        for (int i = 0; i < eszB; i++)
        {
            int enem = enemy[bNum][i];
            int rootE = Find(enem);

            if (rootA == rootE)
                return -2;
        }
    }

    Union(aNum, bNum);
    allies[aNum].push_back({bNum, itB->second.y, itB->second.x});
    allies[bNum].push_back({aNum, itA->second.y, itA->second.x});

    return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
    // allies
    auto itA = country.find(mMonarchA);
    auto itB = country.find(mMonarchB);

    if (itA == country.end() || itB == country.end())
        return -3;

    int numA = itA->second.n;
    int numB = itB->second.n;

    int rootA = Find(numA);
    int rootB = Find(numB);

    if (rootA == rootB)
        return -1;

    // attacker's land is or is not neighboring to victim's land
    int neighbor = 0;
    bool flag = false;
    vector<string> attackers;
    attackers.clear();
    for (int i = 0; i < allies[numA].size(); i++)
    {
        int next = allies[numA][i].n;
        int curr_y = allies[numA][i].y;
        int curr_x = allies[numA][i].x;

        for (int j = 0; j < 8; j++)
        {
            int ny = curr_y + dir[j][0];
            int nx = curr_x + dir[j][1];

            if (ny >= NN || nx >= NN || ny < 0 || nx < 0)
                continue;

            if (General[ny][nx] == mMonarchB)
            {
                neighbor += (Sol[curr_y][curr_x] / 2);
                flag = true;
                // attack
                attackers.push_back(General[curr_y][curr_x]);
                Sol[curr_y][curr_x] -= neighbor;
                break;
            }
        }
    }

    if (!flag)
        return -2;

    // enemy
    enemy[numA].push_back(numB);
    enemy[numB].push_back(numA);

    vector<string> defenders;
    defenders.push_back(mMonarchB);
    int defendSol = Sol[itB->second.y][itB->second.x];
    if (allies[numB].size() != 0)
    {
        int curr_y = itB->second.y;
        int curr_x = itB->second.x;
        for (int j = 0; j < 8; j++)
        {
            int ny = curr_y + dir[j][0];
            int nx = curr_x + dir[j][1];

            if (ny >= NN || nx >= NN || ny < 0 || nx < 0)
                continue;

            int rootE = Find(country.find(General[ny][nx])->second.n);

            if (rootB == rootE)
            {
                defenders.push_back(General[ny][nx]);
                defendSol += (Sol[ny][nx] / 2);
                Sol[ny][nx] -= (Sol[ny][nx] / 2);
            }
        }
    }

    // attackers win
    if (neighbor > defendSol)
    {
        neighbor -= defendSol;
        int curr_y = itB->second.y;
        int curr_x = itB->second.x;
        Sol[curr_y][curr_x] = neighbor;
        // memcpy(General[curr_y][curr_x], mGeneral, sizeof(mGeneral));
        country.insert({mGeneral, {itB->second.n, curr_y, curr_x}});
        country.erase(General[curr_y][curr_x]);

        itB = country.find(mGeneral);
        numB = itB->second.n;

        allies[numB].clear();
        enemy[numB].clear();

        strcpy(General[curr_y][curr_x], mGeneral);
        allies[numA].push_back({numB, curr_y, curr_x});
        allies[numB].push_back({numA, itA->second.y, itA->second.x});

        Union(numA, numB);

        return 1;
    }

    // defenders win
    if (defendSol >= neighbor)
    {
        defendSol -= neighbor;
        Sol[itB->second.y][itB->second.x] = defendSol;
        return 0;
    }

    return -3;
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
    auto it = country.find(mMonarch);
    int num = it->second.n;

    if (mOption == 0)
    {
        Sol[it->second.y][it->second.x] += mNum;
        return Sol[it->second.y][it->second.x];
    }
    else
    {
        int total = Sol[it->second.y][it->second.x];
        for (int i = 0; i < allies[num].size(); i++)
        {
            pos next = allies[num][i];

            total += Sol[next.y][next.x];
        }
        return total;
    }
    return -1;
}

static int run()
{
    int isOK = 0;

    int N;
    int cmd;
    int result;
    int check;

    int mN;
    char mMonarchA[11];
    char mMonarchB[11];
    char mGeneral[11];
    int mOption;
    int num;

    scanf("%d", &N);

    for (int c = 0; c < N; ++c)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            scanf("%d", &mN);
            for (int j = 0; j < mN; j++)
                for (int i = 0; i < mN; i++)
                    scanf("%d", &Sol[j][i]);

            for (int j = 0; j < mN; j++)
                for (int i = 0; i < mN; i++)
                    scanf("%s", General[j][i]);

            init(mN, Sol, General);
            isOK = 1;
            break;

        case CMD_ALLY:
            scanf("%s %s", mMonarchA, mMonarchB);
            result = ally(mMonarchA, mMonarchB);
            scanf("%d", &check);
            if (result != check)
                isOK = 0;
            break;

        case CMD_ATTACK:
            scanf("%s %s %s", mMonarchA, mMonarchB, mGeneral);
            result = attack(mMonarchA, mMonarchB, mGeneral);
            scanf("%d", &check);
            if (result != check)
                isOK = 0;
            break;

        case CMD_RECRUIT:
            scanf("%s %d %d", mMonarchA, &num, &mOption);
            result = recruit(mMonarchA, num, mOption);
            scanf("%d", &check);
            if (result != check)
                isOK = 0;
            break;

        default:
            isOK = 0;
            break;
        }
    }

    destroy();

    return isOK;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        if (run())
            printf("#%d %d\n", tc, MARK);
        else
            printf("#%d %d\n", tc, 0);
    }
    return 0;
}