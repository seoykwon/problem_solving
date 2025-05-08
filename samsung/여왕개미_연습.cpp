#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define f(a, b, c) for (int a = b; a < c; ++a)
using namespace std;
int N;                // 누적된 총 개미집 수
int home[20001];      // i 번 개미집
bool isBroken[20001]; // i번개미집은 철거되었는가?
const int inf = 1e9 + 7;

void input()
{
    cin >> N;
    f(i, 1, N + 1) cin >> home[i];
}

void construct(int p)
{
    home[++N] = p;
}

void remove(int q)
{
    isBroken[q] = true;
}

int search(int workerAnt)
{
    int res = inf;          // 결과로 반환할 최소 최대 이동 거리
    int l = 0, r = inf - 7; // 이분 탐색을 위한 좌우 포인터 (최대 거리 범위)
    int st = -1, ed = -1;   // 현재 그룹의 시작점(st)과 끝점(ed)

    // 이분 탐색 시작
    while (l < r)
    {
        int cnt = 0;            // 현재까지 사용한 개미(workerAnt) 수
        int maxMoveLength = 0;  // 현재 mid 기준으로 나온 최대 이동 거리
        int mid = (l + r) >> 1; // 현재 이분 탐색의 기준 거리

        st = -inf;
        ed = -inf;

        // 1번 집부터 N번 집까지 확인
        f(idx, 1, N + 1)
        {
            if (isBroken[idx])
                continue; // 철거된 개미집은 건너뜀

            // 현재 집이 이전 그룹과 mid 이상 떨어져 있으면 새로운 그룹 시작
            if (home[idx] - st > mid)
            {
                if (++cnt > workerAnt)
                    break; // 개미 수 초과 시 중단 (mid 거리로는 불가능)

                // 이전 그룹의 길이를 최대 이동 거리로 갱신
                maxMoveLength = max(maxMoveLength, ed - st);

                // 새 그룹의 시작점(st)과 끝점(ed) 초기화
                st = home[idx];
                ed = home[idx];
            }
            else
            {
                // 현재 그룹에 포함 가능하므로 끝점 갱신
                ed = home[idx];
            }
        }

        // 마지막 그룹의 길이 반영
        maxMoveLength = max(maxMoveLength, ed - st);

        // 개미 수 초과하면 mid 값을 키움
        if (cnt > workerAnt)
        {
            l = mid + 1;
        }
        else
        {
            // 가능하면 mid 값을 줄이며 탐색
            r = mid;
            res = min(res, maxMoveLength);
        }
    }

    return res; // 최소 최대 이동 거리 반환
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt","r",stdin);
    int Q;
    cin >> Q;
    int p, q, r;
    f(query, 1, Q + 1)
    {
        int cmd;
        cin >> cmd;
        switch (cmd)
        {
        case 100:
            input();
            break;
        case 200:
            cin >> p;
            construct(p);
            break;
        case 300:
            cin >> q;
            remove(q);
            break;
        case 400:
            cin >> r;
            cout << search(r) << '\n';
        default:
            break;
        }
    }

    return 0;
}
