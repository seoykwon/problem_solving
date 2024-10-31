#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands)
{
    vector<int> answer;

    for (int cmd = 0; cmd < commands.size(); cmd++)
    {
        int i = commands[cmd][0];
        int j = commands[cmd][1];
        int k = commands[cmd][2];

        vector<int> tmp(array.begin() + (i - 1), array.begin() + j);

        sort(tmp.begin(), tmp.end());

        answer.push_back(tmp[k - 1]);
    }

    return answer;
}
