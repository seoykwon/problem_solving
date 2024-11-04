#include <iostream>
#include <unordered_map>
#include <cctype>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    string input;
    cin >> input;

    unordered_map<char, int> dic = {
        {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}, {'E', 0}, {'F', 0}};

    for (char c : input)
    {
        c = toupper(c);

        if (dic.count(c) > 0)
        {
            dic[c]++;
        }
    }

    for (char c = 'A'; c <= 'F'; ++c)
    {
        cout << c << ":" << dic[c] << endl;
    }

    return 0;
}