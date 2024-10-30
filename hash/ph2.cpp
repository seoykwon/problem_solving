#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> participant, vector<string> completion)
{

    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());

    for (int i = 0; i < completion.size(); i++)
    {
        if (participant[i] != completion[i])
            return participant[i];
    }
    return participant[participant.size() - 1];
}

// #############################
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

string solution(vector<string> participant, vector<string> completion)
{

    unordered_map<string, int> map;

    for (auto i : participant)
    {
        if (map.find(i) == map.end())
        {
            map[i] = 1;
        }
        else
        {
            map[i]++;
        }
    }

    for (auto i : completion)
    {
        map[i]--;
    }

    for (auto iter = map.begin(); iter != map.end(); iter++)
    {
        if (iter->second == 1)
        {
            return iter->first;
        }
    }
}
