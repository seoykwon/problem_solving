#include <iostream>
#include <string>
#include <vector>
using namespace std;

int T;
vector<string> V;

void Input()
{
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        string S;
        cin >> S;
        V.push_back(S);
    }
}

int Is_Palindrome(int Left, int Right, int Delete, string Str)
{
    while (Left < Right)
    {
        if (Str[Left] != Str[Right])
        {
            if (Delete == 0)
            {
                if (Is_Palindrome(Left + 1, Right, 1, Str) == 0 || Is_Palindrome(Left, Right - 1, 1, Str) == 0)
                    return 1;
                return 2;
            }
            else
                return 2;
        }
        else
        {
            Left++;
            Right--;
        }
    }
    return 0;
}

void Solution()
{
    for (int t = 0; t < T; t++)
    {
        string Str = V[t];
        int Result = Is_Palindrome(0, Str.length() - 1, 0, Str);
        cout << Result << endl;
    }
}

void Solve()
{
    Input();
    Solution();
}

int main(void)
{
    Solve();
}