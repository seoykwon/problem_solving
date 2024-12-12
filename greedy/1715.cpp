#include <iostream>
#include <queue>
using namespace std;

int n;
int ans;
priority_queue<int, vector<int>, greater<int>> pq;

int main(void)
{

    cin >> n;
    if (n == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    int tmp;
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        pq.push(tmp);
    }
    while (!pq.empty())
    {
        int sum = 0;
        sum += pq.top();
        pq.pop();
        if (!pq.empty())
        {
            sum += pq.top();
            pq.pop();
            if (!pq.empty())
                pq.push(sum);
        }
        ans += sum;
    }

    cout << ans << endl;
    return 0;
}

/**
 * https://velog.io/@murraiya/%EB%B0%B1%EC%A4%80-1715%EB%B2%88-C-%EC%B9%B4%EB%93%9C-%EC%A0%95%EB%A0%AC%ED%95%98%EA%B8%B0
 * 위 블로그 글 참고하기
 */