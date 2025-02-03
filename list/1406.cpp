// stack
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
    int M;
    string s = "";
    stack<char> left;
    stack<char> right;

    cin >> s;

    for (int i = 0; i < (int)s.size(); i++)
    {
        left.push(s[i]);
    }

    cin >> M;

    for (int i = 0; i < M; i++)
    {
        char cmd, c;
        cin >> cmd;

        if (cmd == 'L')
        {
            if (!left.empty())
            {
                right.push(left.top());
                left.pop();
            }
        }
        else if (cmd == 'D')
        {
            if (!right.empty())
            {
                left.push(right.top());
                right.pop();
            }
        }
        else if (cmd == 'B')
        {
            if (!left.empty())
            {
                left.pop();
            }
        }
        else if (cmd == 'P')
        {
            cin >> c;
            left.push(c);
        }
    }

    while (!left.empty())
    {
        right.push(left.top());
        left.pop();
    }

    while (!right.empty())
    {
        cout << right.top();
        right.pop();
    }
}

// ##### list
#include <iostream>
#include <string>
#include <list>
using namespace std;

int main()
{
    int M;
    string s = "";
    string ans = "";

    cin >> s;
    list<char> li(s.begin(), s.end());

    auto cursor = li.end();
    cin >> M;

    for (int i = 0; i < M; i++)
    {
        char cmd, c;
        cin >> cmd;

        if (cmd == 'L')
        {
            if (cursor != li.begin())
                cursor--;
        }
        else if (cmd == 'D')
        {
            if (cursor != li.end())
                cursor++;
        }
        else if (cmd == 'B')
        {
            if (cursor != li.begin())
            {
                cursor--;
                cursor = li.erase(cursor);
            }
        }
        else if (cmd == 'P')
        {
            cin >> c;
            li.insert(cursor, c);
        }
    }

    for (cursor = li.begin(); cursor != li.end(); cursor++)
    {
        cout << *cursor;
    }
}