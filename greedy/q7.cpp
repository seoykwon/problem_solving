#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <climits>

using namespace std;

unordered_set<string> mp; // to mark whether current string is visited or not
struct node
{
    string str;
    int order;
};

int bfs(string start, string end)
{
    queue<node> q;
    q.push({start, 0});
    mp.insert(start);

    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        if (now.str == end)
        {
            return now.order;
        }

        // when out of range
        // if you don't do this, "terminate called after throwing an instance of 'std::out_of_range" error appears
        long long tmp = stoll(now.str);
        if (tmp >= LLONG_MAX / 2)
        {
            return -1;
        }

        // multiply
        tmp *= 2;
        string s = to_string(tmp);

        if (mp.find(s) == mp.end())
        {
            mp.insert(s);
            q.push({s, now.order + 1});
        }

        // add one
        string s2 = now.str + "1";
        if (mp.find(s2) == mp.end())
        {
            mp.insert(s2);
            q.push({s2, now.order + 1});
        }
    }
    return -1;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int start, end;
    cin >> start >> end;

    string s, e;
    s = to_string(start);
    e = to_string(end);

    cout << bfs(s, e) << '\n';

    return 0;
}

// ################### 위의 방식 말고 그리디하게 풀기 ##############################

// 역연산이 가능하기 떄문에, 곱해가고 더해가는게 아닌 나누고 빼주는 것으로 처리하자.
// 이 경우, 짝수일때는 나누는 연산, 홀수일때는 맨 끝 1을 빼는 연산 빼고는 불가능해 가능한 연산이 유일하다.
// 따라서, 이 유일한 연산을 가지고 루프를 돌아 체크한다.
#include <iostream>
using namespace std;

int A, B, ans;

int main()
{
    cin >> A >> B;

    while (B >= A)
    {
        if (B == A)
        { // A == B 에 도달 시 출력 후 종료
            cout << ans;
            return 0;
        }

        // 홀수인지 판별하기. 짝수는 (!(B & 1))
        if (B & 1)
        {
            // 만약 나눠가는 진행 도중에 홀수를 만났고, 끝자리가 1이 아니라면 절대 도달할 수 없다.
            if (B % 10 != 1)
                break;
            B /= 10;
        }
        else
            B >>= 1; // 짝수라면 B를 2로 나눈다.

        ans++;
    }

    cout << -1;
}
