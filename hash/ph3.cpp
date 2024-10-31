#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool solution(vector<string> phone_book)
{

    unordered_map<string, int> nums;
    for (auto it = phone_book.begin(); phone_book.end() != it; ++it)
    {
        for (int j = 0; j < it->size() - 1; ++j)
        {
            auto res = nums.insert(make_pair(it->substr(0, j + 1), 0)); // 0 : prefix
            if (false == res.second && res.first->second != 0)
            {
                return false;
            }
        }

        if (false == nums.insert(make_pair(*it, 1)).second) // 1 : full text
        {
            return false;
        }
    }

    return true;
}

// ################################################################

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool solution(vector<string> phoneBook)
{
    sort(phoneBook.begin(), phoneBook.end());

    for (int i = 0; i < phoneBook.size() - 1; i++)
    {
        if (phoneBook[i] == phoneBook[i + 1].substr(0, phoneBook[i].size()))
            return false;
    }

    return true;
}