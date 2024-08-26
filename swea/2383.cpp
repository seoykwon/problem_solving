#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct Coord
{
    int row;
    int col;
};
int calcDist(Coord a, Coord b)
{
    return abs(a.row - b.row) + abs(a.col - b.col);
}
struct Element
{
    Coord person; // 어떤 사람 맵상에서의 좌표
    Coord stair;  // 어떤 계단 맵상에서의 좌표
    bool operator<(Element right) const
    {
        // 거리가 짧은 것 우선
        int lDist = calcDist(person, stair);
        int rDist = calcDist(right.person, right.stair);

        if (lDist < rDist)
            return false;
        if (lDist > rDist)
            return true;

        return false;
    }
};
int N;
int MAP[15][15];
vector<Coord> persons; // 맵 상에서 사람들의 좌표
vector<Coord> stairs;  // 맵 상에서 계단의 좌표
vector<int> path;      // 어떤 계단을 선택했는지 기록용
void init()
{
    memset(MAP, 0, sizeof(MAP));
    persons.clear();
    stairs.clear();
    path.clear();
}
void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 1)
                persons.push_back({i, j});
            else if (MAP[i][j] >= 2)
                stairs.push_back({i, j});
        }
    }
}

int simulation()
{
    // pq를 몇 개 : 2개
    priority_queue<Element> pq[2];
    // path에 기록된대로 계단 별로 나눠서 데이터를 저장
    for (int i = 0; i < path.size(); i++)
    {

        int personNum = i;      // i번 째 사람
        int stairNum = path[i]; // i번째 사람이 선택한 계단
        pq[path[i]].push({persons[i], stairs[stairNum]});
    }
    queue<int> useList; // 계단 내려가기 완료한 시간

    for (int stairNum = 0; stairNum < 2; stairNum++)
    {
        Element now = pq[stairNum].top();
        pq[stairNum].pop();
        // now.person -> now.stair 이동
        // 계단까지 이동 시간
        int arriveTime = calcDist(now.person, now.stair) + 1;
        // 계단을 내려가는 시간
        int stairTime = MAP[now.stair.row][now.stair.col];

        // 3명 미만
        if (useList.size() < 3)
            useList.push(arriveTime + stairTime);
        // 3명이 꽉찬경우
        else
        {
            int prevTime = useList.front();
            useList.pop(); // 맨앞에 사람이 계단을 빠져나감
            if (prevTime > arriveTime)
                useList.push(prevTime + stairTime);
            else
                useList.push(arriveTime + stairTime);
        }
        // 각 계단별로 queue로 사용완료 시간 관리
        // 각 계단별로 A의 소요시간 B의 소요시간
        //  둘 중에 큰거 return
    }

    return ret;
}

void dfs(int now)
{ // 사람들을 순서대로 계단 선택하게 함

    if (now >= persons.size())
    { // 모든 사람들이 계단을 선택
        // path + 기록된 대로 시뮬레이션을 돌려야 함.
        return;
    }

    for (int i = 0; i < 2; i++)
    { // i : now번째 사람이 선택하는 계단

        path.push_back(i);
        dfs(now + 1);
        path.pop_back();
    }
}
void solution()
{
    dfs(0);
}

int main()
{

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        init();
        input();
        solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}