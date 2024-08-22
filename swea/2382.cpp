#include <iostream>
#include <vector>
using namespace std;

int N;
int M; // 격리 시간
int K; // 군집 개수
int ans = 0;
struct Colony
{
    int row, col, cnt, dir;
};
struct MAP
{
    int colonyNum; // 해당 셀을 차지하고 있는 군집의 번호
    int cnt;       //
};
vector<Colony> colony; // 군집 정보 목록
vector<int> alive;     // 살아있는 군집 확인

void input()
{

    cin >> N >> M >> K;
    colony.push_back({0, 0, 0, 0});
    for (int i = 1; i <= K; i++)
    {
        int y, x, cnt, dir;
        cin >> y >> x >> cnt >> dir;
        colony.push_back({y, x, cnt, dir});
        alive.push_back(i); // 살아있는 군집 목록도 기록
    }
}
void simulation()
{

    for (int time = 0; time < M; time++)
    {
        MAP Map[110][110] = {
            0,
        }; // 기본 세팅
        int ydir[] = {0, -1, 1, 0, 0};
        int xdir[] = {0, 0, 0, -1, 0};

        for (int i = 0; i < alive.size(); i++)
        {
            // 살아있는 군집 확인
            int nowColonyNum = alive[i];
            Colony nowColony = colony[nowColonyNum]; // 군집 정보 목록을 가져옴.

            // 일단 움직여야 한다.
            nowColony.row += ydir[nowColony.dir];
            nowColony.col += xdir[nowColony.dir];

            if (nowColony.row >= N - 1 || nowColony.col >= N - 1 ||
                nowColony.row <= 0 || nowColony.col <= 0)
            {
                // 미생물 수가 반으로 준다.
                nowColony.cnt /= 2;
                // 방향이 반대로 상 하 좌 우
                //                1  2  3  4
                nowColony.dir += 1;
                if (nowColony.dir % 2 == 1)
                    nowColony.dir -= 2;
            }

            // 군집 합치기 Map 특정 셸을 차지하고 있는 군집과 비교
            int maxColonyNum = Map[nowColony.row][nowColony.col].colonyNum; // 해당 셀을 차지하고 있는 군집의 번호를 확인
            Colony maxColony = colony[maxColonyNum];                        //

            // nowColony vs maxColony
            if (nowColony.cnt > maxColony.cnt)
            {
                Map[nowColony.row][nowColony.col] = {nowColonyNum,
                                                     Map[nowColony.row][nowColony.col].cnt + nowColony.cnt};
                colony[maxColonyNum].cnt = 0;
            }
            else
            {
                Map[nowColony.row][nowColony.col] = {maxColonyNum,
                                                     Map[nowColony.row][nowColony.col].cnt + nowColony.cnt};
                nowColony.cnt = 0;
            }
            colony[nowColonyNum] = nowColony; // 임시로 다뤘던 군집정보를 업데이트
        }
        // 다음턴을 준비~!!
        vector<int> next_alive;
        for (int i = 0; i < alive.size(); i++)
        {
            int nowColonyNum = alive[i];
            Colony nowColony = colony[nowColonyNum];
            if (nowColony.cnt == 0)
                continue;
            colony[nowColonyNum].cnt = Map[nowColony.row][nowColony.col].cnt;
            next_alive.push_back(nowColonyNum); // 다음턴에 맵에 등장할 군집 목록
        }
        alive = next_alive;
    }
}
void init()
{
    N = M = K = 0;
    alive.clear();
    colony.clear();
    ans = 0;
}

int solution()
{
    simulation();
    int ret = 0;
    for (int i = 0; i < alive.size(); i++)
    {
        ret += colony[alive[i]].cnt;
    }
    return ret;
}

/*
1
7 2 9
1 1 7 1
2 1 7 1
5 1 5 4
3 2 8 4
4 3 14 1
3 4 3 3
1 5 8 2
3 5 100 1
5 5 1 1
*/
int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        init();
        input();
        ans = solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}