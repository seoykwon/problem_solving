#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm> // to use find() function

using namespace std;

struct node
{
    string str;
    int cost;
};
unordered_set<string> visited;

bool oneChar(string a, string b)
{
    int diffCnt = 0;

    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            diffCnt++;
        }
        if (diffCnt > 1)
            return false;
    }
    return true;
    //     return diffCnt == 1;
}

int bfs(string begin, string target, const vector<string> &words)
{
    queue<node> q;
    q.push({begin, 0});
    visited.insert(begin);

    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        if (now.str == target)
        {
            return now.cost;
        }

        for (string word : words)
        {
            if (oneChar(now.str, word) && !visited.count(word))
            {
                q.push({word, now.cost + 1});
                visited.insert(word);
            }
        }
    }
    return 0;
}

int solution(string begin, string target, vector<string> words)
{
    int answer = 0;

    if (find(words.begin(), words.end(), target) == words.end())
        return 0; // target이 없으면 0 반환

    answer = bfs(begin, target, words);

    return answer;
}