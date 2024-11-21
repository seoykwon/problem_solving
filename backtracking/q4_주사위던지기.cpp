/**
 * M = 1 : 주사위를 N번 던져서 나올 수 있는 모든 경우
 * M = 2 : 주사위를 N번 던져서 중복이 되는 경우를 제외하고 나올 수 있는 모든 경우
 * M = 3 : 주사위를 N번 던져서 모두 다른 수가 나올 수 있는 모든 경우
 * 중복의 예
 * 1 1 2 와 중복 : 1 2 1, 2 1 1
 * 1 2 3 과 중복 : 1 3 2, 2 1 3, 2 3 1, 3 1 2​, 3 2 1
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int path[6] = {0}; // Array to store the current path
int n, type;
bool used[7] = {0}; // Track if a number (1 to 6) is used

void func(int now)
{
    // Type 1: All possible outcomes with duplicates
    if (now >= n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= 6; i++)
    {
        path[now] = i;
        func(now + 1);
    }
}

void func2(int now)
{
    // Type 2: Unique combinations with duplicates allowed
    if (now >= n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= 6; i++)
    {
        if (now > 0 && path[now - 1] > i)
            continue; // Ensure non-decreasing order
        path[now] = i;
        func2(now + 1);
    }
}

void func3(int now)
{
    // Type 3: All unique permutations with all dice showing different numbers
    if (now >= n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= 6; i++)
    {
        if (used[i])
            continue; // Skip if number is already used
        path[now] = i;
        used[i] = true;
        func3(now + 1);
        used[i] = false; // Backtrack
    }
}

int main()
{
    cin >> n >> type;

    if (type == 1)
    {
        func(0);
    }
    else if (type == 2)
    {
        func2(0);
    }
    else if (type == 3)
    {
        func3(0);
    }

    return 0;
}

// ########################### 강사님 코드 #################################
#include <iostream>
using namespace std;

int N;        // 주사위의 수
int M;        // mode
int path[10]; // 경로/경우의 수 기록

void printpath(int level)
{
    for (int i = 0; i < level; i++)
        cout << path[i] << " ";
    cout << '\n';
}

void roll1(int level)
{
    // 기저 조건 -> N개의 주사위를 던졌다면 종료
    if (level == N)
    {
        printpath(level);
        return;
    }

    // 수행
    // 재귀 구성 -> 6개의 경우의 수를 가지고 내려갈 수 있다.
    for (int i = 1; i <= 6; i++)
    {
        path[level] = i;  // level번 주사위는 i번 눈금을 굴렸다
        roll1(level + 1); // 이 경우의 수를 가지고 다음 주사위를 굴린다.
        path[level] = 0;  // path 기록 초기화
    }
}

void roll2(int level)
{
    // 기저 조건 -> N개의 주사위를 던졌다면 종료
    if (level == N)
    {
        printpath(level);
        return;
    }

    // 수행
    // 재귀 구성 -> 6개의 경우의 수를 가지고 내려갈 수 있다.
    for (int i = 1; i <= 6; i++)
    {
        // 가지치기 -> 작은 조합부터 출력한다
        // 즉 i번째 눈금이 i-1번째 눈금보다 작다면,
        // 이에 대한 더 작은 조합/경우의 수는 이미 출력되었음이 확정된다.
        if (level > 0 && i < path[level - 1])
            continue;
        path[level] = i;  // level번 주사위는 i번 눈금을 굴렸다
        roll2(level + 1); // 이 경우의 수를 가지고 다음 주사위를 굴린다.
        path[level] = 0;  // path 기록 초기화
    }
}

// index : 주사위의 눈금
// value : 해당 눈금을 사용(굴린적)한 적이 있는가?
int DAT[10];

void roll3(int level)
{
    // 기저 조건 -> N개의 주사위를 던졌다면 종료
    if (level == N)
    {
        printpath(level);
        return;
    }

    // 수행
    // 재귀 구성 -> 6개의 경우의 수를 가지고 내려갈 수 있다.
    for (int i = 1; i <= 6; i++)
    {
        // 가지치기 -> 이미 사용한 눈금이면 pass
        if (DAT[i] == 1)
            continue;
        DAT[i] = 1;       // level 층에서 지금 i번 눈금을 사용한다.
        path[level] = i;  // level번 주사위는 i번 눈금을 굴렸다
        roll3(level + 1); // 이 경우의 수를 가지고 다음 주사위를 굴린다.
        path[level] = 0;  // path 기록 초기화
        DAT[i] = 0;       // DAT - i번 눈금 사용 기록 초기화
    }
}

int main()
{
    cin >> N >> M;
    if (M == 1)
        roll1(0);
    if (M == 2)
        roll2(0);
    if (M == 3)
        roll3(0);
}