#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

// 필요한 비용 계산 함수
bool canMake(int mid, int M, const vector<vector<int>> &parts)
{
    long long totalCost = 0;

    for (const auto &part : parts)
    {
        int K = part[0], X = part[1];
        int Sk = part[2], Sp = part[3];
        int Bk = part[4], Bp = part[5];

        // 부족한 부품 개수
        int needed = max(0, K * mid - X);

        // 소형 패키지와 대형 패키지로 필요한 부품을 구매
        if (needed > 0)
        {
            int minCost = INT_MAX;

            // 소형 패키지만 사용
            int smallPackages = ceil((double)needed / Sk);
            minCost = min(minCost, smallPackages * Sp);

            // 대형 패키지만 사용
            int largePackages = ceil((double)needed / Bk);
            minCost = min(minCost, largePackages * Bp);

            // 소형 + 대형 패키지 조합
            for (int i = 0; i <= largePackages; ++i)
            {
                int remaining = needed - (i * Bk);
                if (remaining <= 0)
                {
                    minCost = min(minCost, i * Bp);
                }
                else
                {
                    int smallPackages = ceil((double)remaining / Sk);
                    minCost = min(minCost, i * Bp + smallPackages * Sp);
                }
            }

            totalCost += minCost;
            if (totalCost > M)
                return false; // 예산 초과
        }
    }
    return totalCost <= M;
}

// 이진 탐색으로 최대 우주선 개수 찾기
int findMaxSpaceships(int N, int M, const vector<vector<int>> &parts)
{
    int left = 0, right = 1e6; // 이론상 최대 우주선 수 설정
    int ans = 0;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (canMake(mid, M, parts))
        {
            ans = mid; // 더 많은 우주선을 만들 수 있는지 탐색
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return ans;
}

int main()
{
    // freopen("input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> parts(N, vector<int>(6));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            cin >> parts[i][j];
        }
    }

    cout << findMaxSpaceships(N, M, parts) << endl;

    return 0;
}

// ###################################################################
#include <bits/stdc++.h>
using namespace std;

int N, M, K[101], X[101], Sk[101], Sp[101], Bk[101], Bp[101]; // 변수들

// binary search 성공 합수
bool chk(int k)
{
    // 주어진 예산 안에서 k개를 만들 수 있으면 true다.    // k개를 만들 수 있는가에 대해서는, 각각의 부품 종류의 패키지들은 독립적임을 생각하자.
    // 따라서, 각각의 부품에 대해 필요 수량을 최소 금액으로 사서 M원 안에 드는지를 보면 된다.
    int tot = 0;
    for (int i = 0; i < N; i++)
    {
        int missing = k * K[i] - X[i]; // 부족한 부품 개수
        if (missing <= 0)
            continue; // 안 부족함

        int sp_pea = Bk[i] * Sp[i], bp_pea = Sk[i] * Bp[i]; // 개당 가격 비교

        if (sp_pea <= bp_pea)
        { // 소형 패키지가 개당 가격이 더 싸면 그걸로만 채우자.
            tot += (missing + Sk[i] - 1) / Sk[i] * Sp[i];
        }
        else
        { // 아니라면 대강은 큰 패키지로 채우고 나머지를 어떻게 할지 케웍
            tot += missing / Bk[i] * Bp[i];
            int remain = missing % Bk[i];
            int sp_rep = (remain + Sk[i] - 1) / Sk[i] * Sp[i];
            tot += min(Bp[i], sp_rep);
        }

        if (tot > M)
            return false; // 총 비용 초과시 false
    }

    return true;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0); // Fast I/O
    // 입력 받기
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> K[i] >> X[i] >> Sk[i] >> Sp[i] >> Bk[i] >> Bp[i];
    }
    // binary search
    int l = 0, r = 101, res = -1;
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (chk(m))
        {
            res = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }

    cout << res << '\n';
}
