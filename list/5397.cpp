#include <iostream>
#include <string>
#include <list>
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    while (n--)
    {
        string str;
        cin >> str;

        int sz = (int)str.size();

        list<char> li;
        // why list<char> li(str.begin(), str.end()) did not work?

        auto cursor = li.begin();

        for (int i = 0; i < sz; i++)
        {
            char now = str[i];

            if (now == '<')
            {
                if (cursor != li.begin())
                {
                    cursor--;
                }
            }
            else if (now == '>')
            {
                if (cursor != li.end())
                {
                    cursor++;
                }
            }
            else if (now == '-')
            {
                if (cursor != li.begin())
                {
                    cursor = li.erase(--cursor);
                }
            }
            else
            {
                li.insert(cursor, now);
            }
        }

        for (cursor = li.begin(); cursor != li.end(); cursor++)
        {
            cout << *cursor;
        }
        cout << '\n';
    }
}