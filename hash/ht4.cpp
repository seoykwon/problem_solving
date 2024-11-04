#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
    int N;
    cin >> N;

    struct vote
    {
        int good = 0;
        int bad = 0;
    };

    unordered_map<string, vote> votes;

    for (int i = 0; i < N; i++)
    {
        string goodf, badf;
        cin >> goodf >> badf;

        votes[goodf].good++;
        votes[badf].bad++;
    }

    int goodcnt = 0;
    int badcnt = 0;
    int strangecnt = 0;

    for (auto entry : votes)
    {
        string friendname = entry.first;
        vote votecnt = entry.second;

        if (votecnt.good > votecnt.bad)
        {
            goodcnt++;
        }
        else if (votecnt.good < votecnt.bad)
        {
            badcnt++;
        }
        else
        {
            strangecnt++;
        }
    }

    cout << goodcnt << " " << badcnt << " " << strangecnt << endl;
}