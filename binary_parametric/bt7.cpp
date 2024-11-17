#include <iostream>
#include <vector>
using namespace std;

// 룰을 정의하는 구조체
struct Rule
{
    int a, b, c; // 시작 상자, 끝 상자, 간격
};

// 특정 박스 번호까지 누적된 쿠폰 개수를 계산하는 함수
long long countCouponsUntil(int box, const vector<Rule> &rules)
{
    long long count = 0;
    for (const auto &rule : rules)
    {
        if (box < rule.a)
            continue;                   // 현재 박스가 시작점보다 작으면 무시
        int lastBox = min(box, rule.b); // 현재 박스와 룰의 끝점 중 더 작은 값까지 계산
        count += (lastBox - rule.a) / rule.c + 1;
    }
    return count;
}

// 이분 탐색을 통해 마지막 쿠폰이 들어갈 상자 번호 찾기
int findLastBox(int n, int k, const vector<Rule> &rules)
{
    int left = 1, right = n;
    int answer = n; // 마지막 쿠폰이 들어갈 상자 번호를 저장할 변수
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (countCouponsUntil(mid, rules) >= k)
        {
            answer = mid; // 조건을 만족하면 답을 갱신하고 더 작은 상자 번호 탐색
            right = mid - 1;
        }
        else
        {
            left = mid + 1; // 조건을 만족하지 않으면 더 큰 상자 번호 탐색
        }
    }
    return answer;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<Rule> rules(m); // 룰을 저장할 벡터
    for (int i = 0; i < m; ++i)
    {
        cin >> rules[i].a >> rules[i].b >> rules[i].c;
    }

    // 마지막 쿠폰이 들어갈 상자 번호 출력
    cout << findLastBox(n, k, rules) << endl;
    return 0;
}
