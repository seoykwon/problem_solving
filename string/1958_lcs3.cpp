#include <iostream>
#include <algorithm>
#include <string>
#define MAX 101 // 문자열 최대 길이 (문제에서 주어짐)

using namespace std;

// 3차원 LCS 배열: LCS[i][j][k]는
// 문자열 a의 i번째, b의 j번째, c의 k번째까지의 LCS 길이를 의미
int LCS[MAX][MAX][MAX] = {0};

int main()
{
    ios::sync_with_stdio(false); // C와 C++ 표준 입출력 동기화를 끔 (입출력 속도 향상)
    cin.tie(0);                  // cin과 cout의 연결을 끊음 (입출력 속도 향상)

    int i, j, k;
    string a, b, c;

    // 세 문자열 입력 받음
    cin >> a >> b >> c;

    int save = 0; // 최종적으로 가장 긴 공통 부분 수열(LCS)의 길이를 저장

    int alen = a.length();
    int blen = b.length();
    int clen = c.length();

    // 초기값 설정은 위에서 이미 배열을 0으로 초기화했으므로 생략 가능
    LCS[0][0][0] = 0;

    // 세 문자열 각각의 모든 접두사에 대해 LCS 계산
    for (i = 1; i <= alen; i++)
    {
        for (j = 1; j <= blen; j++)
        {
            for (k = 1; k <= clen; k++)
            {
                // 현재 위치의 문자가 세 문자열 모두에서 일치할 경우
                if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
                {
                    // 세 문자가 모두 같으면, 이전까지의 공통 수열 + 1
                    LCS[i][j][k] = LCS[i - 1][j - 1][k - 1] + 1;
                }
                else
                {
                    // 문자가 일치하지 않으면, 세 방향 중 최댓값으로 LCS 갱신
                    // (한 문자열을 하나 줄여가며 비교)
                    LCS[i][j][k] = max(
                        max(LCS[i - 1][j][k], LCS[i][j - 1][k]),
                        LCS[i][j][k - 1]);
                }
                // 지금까지 찾은 최댓값 저장
                save = max(save, LCS[i][j][k]);
            }
        }
    }

    // 최장 공통 부분 수열의 길이 출력
    cout << save;

    return 0;
}
