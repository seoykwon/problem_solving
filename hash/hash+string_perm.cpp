#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    unordered_map<char, vector<char>> mp{
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}};

    vector<string> answer;

    void dfs(string &digits, int index, string cur)
    {
        if (cur.size() == digits.size())
        {
            answer.push_back(cur);
            return;
        }

        // Get the current digit and its corresponding letters
        char digit = digits[index];
        vector<char> letters = mp[digit];

        // Explore each letter for the current digit
        for (char letter : letters)
        {
            dfs(digits, index + 1, cur + letter);
        }
    }

    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return {};
        answer.clear();     // Clear previous results
        dfs(digits, 0, ""); // Start DFS from the first digit
        return answer;
    }
};