#include <iostream>
#include <unordered_map>

using namespace std;

struct team
{
    int membercnt;
    int sumscore;
};

int main()
{
    unordered_map<string, team> mp;

    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string team;
        int score;

        cin >> team >> score;
        // if team nonexistent
        if (mp.find(team) == mp.end())
        {
            mp.insert({team, {1, score}});
        }
        // if team already exists
        else
        {
            mp[team].membercnt++;
            mp[team].sumscore += score;
        }
    }

    string coco;
    string fr;

    cin >> coco >> fr;

    cout << mp[coco].membercnt << " " << mp[coco].sumscore << endl;
    cout << mp[fr].membercnt << " " << mp[fr].sumscore << endl;

    if (mp[coco].sumscore > mp[fr].sumscore)
    {
        cout << coco << endl;
    }
    else
    {
        cout << fr << endl;
    }
}