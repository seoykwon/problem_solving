#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct meeting
{
    int start;
    int end;
};

bool cmp(meeting a, meeting b)
{
    if (a.end < b.end)
        return true;
    if (a.end > b.end)
        return false;
    if (a.start < b.start)
        return true;
    if (a.start > b.start)
        return false;
    return false;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    vector<meeting> m;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;

        m.push_back({a, b});
    }

    sort(m.begin(), m.end(), cmp);

    int cnt = 1;
    int time = m[0].end;

    for (int i = 1; i < n; i++)
    {
        if (m[i].start >= time)
        {
            cnt++;
            time = m[i].end;
        }
    }
    cout << cnt << '\n';
    return 0;
}