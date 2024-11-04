#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;

    cin >> N >> M;

    unordered_map<string, int> mp;
    vector<string> answer;
    int cnt = 0;

    for (int i = 0; i < N; i++)
    {
        string tmp;
        cin >> tmp;

        mp.insert({tmp, 1});
    }

    for (int i = 0; i < M; i++)
    {
        string tmp;
        cin >> tmp;

        if (mp.find(tmp) != mp.end())
        {
            cnt++;
            answer.push_back(tmp);
        }
    }

    cout << cnt << endl;
    // 사전순으로 출력
    sort(answer.begin(), answer.end());
    for (int i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << endl;
    }
}