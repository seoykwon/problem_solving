#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> a, vector<int> b)
{
    if (a[1] < b[1])
        return true;
    if (a[1] > b[1])
        return false;
    return false;
}

int solution(vector<vector<int>> sizes)
{
    int answer = 0;

    for (int i = 0; i < sizes.size(); i++)
    {
        sort(sizes[i].begin(), sizes[i].end());
    }
    sort(sizes.begin(), sizes.end(), cmp);

    int w = 0;
    int h = 0;

    for (int i = 0; i < sizes.size(); i++)
    {
        w = max(w, sizes[i][0]);
        h = max(h, sizes[i][1]);
    }
    answer = w * h;

    return answer;
}