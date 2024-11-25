#include <iostream>
#include <vector>
using ll = long long;
using namespace std;

int N, M, arr[5][5];
// 답은 64비트 범위일 수도 있다.
ll ans;
vector<int> shifts; // n 번째 행이 몇 칸 돌아가 있는지를 나타낸다.

void solve(int idx, int shi)
{
    if (idx >= N)
    {               // 모든 행들에 대해 돌리기가 확정일 때
        ll mul = 1; // 곱 저장
        for (int j = 0; j < M; j++)
        {
            int prv = 1e9, sum = 0; // prv = 이전 수, sum =  열의 합
            for (int i = 0; i < N; i++)
            {
                int cur = arr[i][(j + shifts[i]) % M];
                if (prv == cur)
                    return; // 만약 같은 수가 한번이라도 일직선상 연속이라면 그냥 종료
                sum += cur;
                prv = cur;
            }

            mul *= sum; // 총 곱에 합을 곱해줌
        }
        ans = max(ans, mul); // 정상적으로 처리되면 ans에 반영
        return;
    }
    shifts.push_back(shi); // shi 만큼 회전시켰음을 표시
    for (int i = 0; i < M; i++)
        solve(idx + 1, i); // 모든 가능한 다음 행 회전에 대해 체크
    shifts.pop_back();     // 복구
}

int main()
{
    // 입력
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            cin >> arr[i][j];
        }
    // 백트래킹
    solve(0, 0);
    cout << ans;
}