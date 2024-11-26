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

// ##################### 강사님 코드 ##################################
#include <iostream>
using namespace std;

int N;
int M;
int tower[5][5];
long long MAX = -21e8;
int path[5];

// 지금 층까지의 회전값을 적용했을 때, 세로 방향에 동일한 값이 있는지 확인할 함수
bool isValid(int level)
{
    // 세로방향으로 확인
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < level; j++)
        {
            // 현재 층 vs 현재 기준으로 위 층들과 각 값들을 확인
            // 각 층에는 path에 기록된 해당 층에 대한 회전값을 적용
            // 만약 동일한 값이 존재한다면, false
            if (tower[level][(i + path[level]) % M] == tower[j][(i + path[j]) % M])
                return false;
        }
    }
    return true;
}

long long calculate()
{
    long long res = 1;
    for (int i = 0; i < M; i++)
    {
        int sum = 0;
        for (int j = 0; j < N; j++)
        {
            // 각 층들에 대해 회전값을 적용한 값들의 합을 구한다
            sum += tower[j][(i + path[j]) % M];
        }
        res *= sum;
    }
    return res;
}

void func(int level)
{
    // 기저 조건 -> N층까지 모두 회전시켜봤고, 동일한 세로 값이 없다면
    if (level == N)
    {
        long long temp = calculate();
        if (temp > MAX)
            MAX = temp;
        return;
    }

    // 재귀 구성 -> 한 층에서 돌려볼 수 있는 경우의 수는 0번 ~ M - 1번의 회전
    for (int i = 0; i < M; i++)
    {
        path[level] = i; // 이번 층에서 i번 만큼을 회전시킨다

        // 가지치기 -> 만약 이번 층까지의 회전값이 "유효하다면" 다음 층으로 간다
        if (isValid(level))
            func(level + 1);

        path[level] = 0; // 기록 초기화
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> tower[i][j];
        }
    }

    func(0);
    cout << MAX;
    return 0;
}