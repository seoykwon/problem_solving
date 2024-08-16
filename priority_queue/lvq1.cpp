#include <iostream>
#include <queue>
#include <string>

using namespace std;

// 1번
struct alphabet
{
    int id;
    char c;
};

// 2번
struct cmp
{
    bool operator()(alphabet &left, alphabet &right)
    {
        return left.c < right.c;
    }
};

priority_queue<alphabet, vector<alphabet>, cmp>
    t;

int main()
{
    // freopen("input.txt", "r", stdin);
    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i++)
    {
        t.push({i, s[i]});
    }

    while (!t.empty())
    {

        auto now = t.top();
        t.pop();
        cout << now.c;
    }
}