// ################################
#include <bits/stdc++.h>
using namespace std;

int N, T, arr[1001]; // N, T, 배열

// binary search 성공 합수
bool chk(int k, int t)
{
    // N <= 500 이므로, O(N^2)에 걸쳐 가능한 범위를 모두 확인해도 된다.
    // [0, N) 까지 시작점을 다르게 해서 크기 N의 슬라이딩 윈도우를 체크한다.
    // 미리 배열 길이를 2배로 늘려놨으므로, 원형에 대한 고려는 되어있다.
    // 합이 k를 넘지 않는 선에서 그리디하게 팀을 구성한다.
    for (int idx = 0; idx < N; idx++)
    {
        int cur_sum = 0, tmp_t = 1, flag = 1; // 현재 팀의 지능 합, 현재 팀 수, 성공 플래그
        for (int i = idx; i < idx + N; i++)
        {
            if (arr[i] > k)
                return false; // 원소 하나가 목표 지능 합보다 커도 무조건 실패다.
            if (cur_sum + arr[i] > k)
            {
                cur_sum = arr[i];
                if (++tmp_t > t)
                { // 팀의 수를 더 많이 나눠야 한다면, 실패다.
                    flag = 0;
                    break;
                }
            }
            else
                cur_sum += arr[i];
        }
        if (flag)
            return true; // 성공 시 리턴
    }

    return false;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0); // Fast I/O
    // 입력 받기
    cin >> N >> T;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
        arr[i + N] = arr[i]; // 원형이므로 길이 2배를 해서 표시
    }

    int l = 1, r = 1e9; // binary search 기본값
    // Head Sum max의 min 값에 대해 binary search
    while (l < r)
    {
        int m = l + r >> 1;
        if (chk(m, T))
            r = m;
        else
            l = m + 1;
    }

    cout << l << '\n';
}

// ################## 강사님 코드 ##############################
#include <iostream>

using namespace std;

int n, t;
int arr[501];
int total = 0;
int maxval = -1;

int maketeam(int val)
{
    int team = 21e8;

    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        int cnt = 1;

        for (int j = i; j < i + n; j++)
        {
            if (sum + arr[j % n] <= val)
                sum += arr[j % n];
            else
            {
                sum = arr[j % n];
                cnt++;
            }
        }
        if (cnt < team)
            team = cnt;
    }
    return team;
}

int binarysearch()
{
    int left = maxval;
    int right = total;
    int ans;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int team = maketeam(mid);

        if (team > t)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
            ans = mid;
        }
    }
    return ans;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n >> t;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if (arr[i] > maxval)
            maxval = arr[i];
        total += arr[i];
    }
    cout << binarysearch();
}