#include <iostream>
#include <vector>
using namespace std;
/*
1
20 3
2 2 3 2 2 2 2 3 3 4 4 3 2 2 3 3 3 2 2 3
4 4 1 4 4 1 4 4 1 1 1 4 1 4 3 3 3 3 3 3
4 4 1 100
7 10 3 40
6 3 2 70
*/
struct BC
{
    int y, x, c, p;
};

vector<BC> bclist;
int M;          // 시뮬레이션 시간
int A;          // BC의 개수
int alist[101]; // 사용자 A의 이동정보
int blist[101]; //
int ydir[] = {0, -1, 0, 1, 0};
int xdir[] = {0, 0, 1, 0, -1};
int ans = 0;

void input()
{
    cin >> M >> A;
    for (int i = 0; i < M; i++)
        cin >> alist[i];
    for (int i = 0; i < M; i++)
        cin >> blist[i];
    for (int i = 0; i < A; i++)
    {
        int y, x, c, p;
        cin >> x >> y >> c >> p;
        bclist.push_back(BC({y, x, c, p})); // 좌표만 순서 바꿔서 넣어줌.
    }
}
int check(int bcnum, int y, int x)
{
    // 어떤 BC 확인하고,
    int bcy = bclist[bcnum].y;
    int bcx = bclist[bcnum].x;
    int c = bclist[bcnum].c;
    int p = bclist[bcnum].p;

    // 범위 계산
    int dist = abs(y - bcy) + abs(x - bcx);

    // 범위안에 들어왔다면 충전량을 돌려준다.

    if (dist <= c)
        return p;
    return 0;
}

int calc(int ay, int ax, int by, int bx)
{
    // 현재 좌표에서 최대 충전량을 계산
    // A와 B의 충전량을 각각 계산을 한다.
    int maxcharge = -1;
    for (int a_cnt = 0; a_cnt < A; a_cnt++)
    {
        for (int b_cnt = 0; b_cnt < A; b_cnt++)
        {
            int sum_charge = 0;
            int Acharge = check(a_cnt, ay, ax);
            int Bcharge = check(b_cnt, by, bx);
            // 충전소가 다른 경우
            if (a_cnt != b_cnt)
            {
                sum_charge = Acharge + Bcharge;
            }
            else
            {
                sum_charge = max(Acharge, Bcharge);
            }
            if (sum_charge > maxcharge)
                maxcharge = sum_charge;

            // 같은 경우 A , B 비교해서 충전이 더 많이 되는 쪽으로 선택
        }
    }
    return maxcharge;
}

void solution()
{
    // 시작점에서 사용자가 출발해서
    // 시뮬레이션 시간동안 최대 충전량을 계산하는 기능
    int ay = 1;
    int ax = 1;
    int by = 10;
    int bx = 10;

    for (int t = 0; t <= M; t++)
    {
        ans += calc(ay, ax, by, bx);

        // 이동하는 코드도 필요
        ay += ydir[alist[t]];
        ax += xdir[alist[t]];
        by += ydir[blist[t]];
        bx += xdir[blist[t]];
    }
}
void init()
{
    ans = 0;
    bclist.clear();
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