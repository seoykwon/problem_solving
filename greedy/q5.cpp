#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct meeting
{
    int start;
    int end;
};

vector<meeting> v;

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
    int n;
    cin >> n;

    while (n--)
    {
        int s, e;
        cin >> s >> e;

        meeting m = {s, e};

        v.push_back(m);
    }
    sort(v.begin(), v.end(), cmp);

    int idxTime = 0;
    int cnt = 0;

    for (int i = 0; i < v.size(); i++)
    {
        // cout << v[i].start << " " << v[i].end << endl;

        if (v[i].start >= idxTime)
        {
            cnt++;
            idxTime = v[i].end;
        }
    }
    cout << cnt;
}