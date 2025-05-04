#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <unordered_map>
#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <unordered_set>

using namespace std;

#define MAX_N 25
#define MAX_L 10

static int Sol[MAX_N][MAX_N];
static char General[MAX_N][MAX_N][MAX_L + 1];

int NN;
struct pos
{
    int n;
    int y;
    int x;
};
unordered_map<string, pos> country;
unordered_map<int, string> rev;
unordered_map<int, unordered_set<int>> enemy;
int parent[MAX_N * MAX_N + 1] = {
    0,
};

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

            rev.insert({cnt, mMonarch[i][j]});
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
    for (int enem : enemy[rootA])
    {
        if (Find(enem) == rootB)
            return -1;
    }
    for (int enem : enemy[rootB])
    {
        if (Find(enem) == rootA)
            return -1;
    }

    Union(aNum, bNum);

    return 1;
}

int isAdjacent(int y1, int x1, int y2, int x2)
{
    for (int d = 0; d < 8; d++)
    {
        int ny = y1 + dir[d][0];
        int nx = x1 + dir[d][1];

        if (ny >= NN || nx >= NN || ny < 0 || nx < 0)
            continue;

        if (ny == y2 && nx == x2)
        {
            return Sol[y1][x1] / 2;
        }
    }
    return 0;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
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

    if (enemy[rootA].find(rootB) == enemy[rootA].end())
        return -1;

    int ay = itA->second.y, ax = itA->second.x;
    int by = itB->second.y, bx = itB->second.x;

    int aSoldier = 0;
    int bSoldier = Sol[by][bx];

    enemy[aNum].insert(bNum);
    enemy[bNum].insert(aNum);

    for (int i = 1; i <= NN * NN; i++)
    {
        if (Find(i) == rootA)
        {
            string name = rev.find(i)->second;
            pos coordinate = country.find(name)->second;
            int curr_x = coordinate.x;
            int curr_y = coordinate.y;

            aSoldier += isAdjacent(curr_y, curr_x, by, bx);
        }
    }
    for (int i = 1; i <= NN * NN; i++)
    {
        if (Find(i) == rootB)
        {
            string name = rev.find(i)->second;
            pos coord = country.find(name)->second;
            int curr_y = coord.y;
            int curr_x = coord.x;

            bSoldier += isAdjacent(curr_y, curr_x, by, bx);
        }
    }

    if (aSoldier > bSoldier)
    {
        Sol[by][bx] = aSoldier - bSoldier;

        for (int i = 1; i <= NN * NN; i++)
        {
            if (Find(i) == rootB)
            {
                auto mp = rev.find(i);
                auto cit = country.find(mp->second);

                country.erase(mp->second);
                rev.erase(i);

                enemy[i].clear();
            }
        }
        strcpy(General[by][bx], mGeneral);
        country[mGeneral] = {bNum, by, bx};
        rev[bNum] = mGeneral;

        parent[bNum] = bNum;

        return 1;
    }
    else
    {
        Sol[by][bx] = bSoldier - aSoldier;

        return 0;
    }
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
    auto it = country.find(mMonarch);
    int num = it->second.n;
    int target = Find(num);

    if (mOption == 0)
    {
        Sol[it->second.y][it->second.x] += mNum;
        return Sol[it->second.y][it->second.x];
    }
    else
    {
        int total = 0;

        for (int i = 1; i <= NN * NN; i++)
        {
            if (Find(i) == target)
            {
                auto mp = rev.find(i);
                it = country.find(mp->second);
                int check = Sol[it->second.y][it->second.x];
                Sol[it->second.y][it->second.x] += mNum;
                total += (Sol[it->second.y][it->second.x]);
            }
        }
        return total;
    }
    return -1;
}
