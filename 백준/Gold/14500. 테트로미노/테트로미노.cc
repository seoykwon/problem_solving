#include <iostream>
using namespace std;

int N, M;

int MAP[500][500];
int visited[500][500];
int ans = -2134567890;
int cnt = 0;
int sum = 0;

int tydir[4][4] = {
    {0, 0, -1, 0},
    {0, 1, 1, 2},
    {0, -1, 0, 1},
    {0, 0, 0, 1},
};
int txdir[4][4] = {
    {0, 1, 1, 2},
    {0, 0, 1, 0},
    {0, 1, 1, 1},
    {0, 1, 2, 1},
};

// 오른쪽 왼쪽 아래쪽 위쪽
int ydir[] = {0, 0, 1, -1};
int xdir[] = {1, -1, 0, 0};

void tshape(int y, int x)
{

    for (int i = 0; i < 4; i++)
    {
        int sum = 0;
        for (int j = 0; j < 4; j++)
        {
            int ny = y + tydir[i][j];
            int nx = x + txdir[i][j];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M)
            {
                break;
            }
            sum += MAP[ny][nx];
        }
        if (sum > ans)
            ans = sum;
    }
}

void dfs(int y, int x)
{

    // 기저 조건
    if (cnt == 4)
    {
        if (sum > ans)
            ans = sum; // 최대값 갱신
        return;
    }

    // 재귀 구성
    for (int i = 0; i < 4; i++)
    {
        int ny = y + ydir[i];
        int nx = x + xdir[i];
        // 예외 처리
        if (ny < 0 || nx < 0 || ny >= N || nx >= M)
        {
            continue;
        }
        if (visited[ny][nx] == 1)
        {
            continue;
        }
        visited[ny][nx] = 1;
        cnt++;
        sum += MAP[ny][nx];
        // 가라
        dfs(ny, nx);
        // 복구
        visited[ny][nx] = 0;
        cnt--;
        sum -= MAP[ny][nx];
    }
}

int main()
{

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            // 4가지 모양에 대해서
            visited[i][j] = 1;
            sum += MAP[i][j];
            cnt++;

            dfs(i, j);

            visited[i][j] = 0;
            sum -= MAP[i][j];
            cnt--;
            // + ㅜ 자 모양 처리
            tshape(i, j);
        }
    }
    cout << ans;

    return 0;
}