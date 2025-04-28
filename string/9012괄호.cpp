#include <iostream>
#include <stack>
using namespace std;

int T;

string checkVPS(string input)
{
    stack<char> ps;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(')
        {
            ps.push('(');
        }
        else
        {
            if (ps.empty())
                return "NO";
            ps.pop();
        }
    }
    if (ps.empty())
    {
        return "YES";
    }
    else
    {
        return "NO";
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    string ps;

    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> ps;
        cout << checkVPS(ps) << '\n';
    }
}