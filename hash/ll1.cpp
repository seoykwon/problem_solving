#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    unordered_map<string, vector<int>> mp;

    for (int i = 0; i < n; i++)
    {
        string name;
        int age;
        cin >> name >> age;
        mp[name].push_back(age);
    }

    string spy;
    vector<int> spy_age;

    for (auto entry : mp)
    {
        if (entry.second.size() > 1)
        {
            spy = entry.first;
            spy_age = entry.second;
            break;
        }
    }

    if (!spy_age.empty())
    {
        cout << spy << endl;
        sort(spy_age.begin(), spy_age.end());
        for (int age : spy_age)
        {
            cout << age << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "no spy" << endl;
    }
}