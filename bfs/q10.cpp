#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, k;
vector<int> b1;
vector<int> b2;
int visited1[100001] = {0};
int visited2[100001] = {0};

void input()
{
    freopen("input.txt", "r", stdin);
    cin >> n >> k;

    string s;
    cin >> s;
    string s2;
    cin >> s2;

    for (char c : s)
    {
        b1.push_back(c - '0');
    }

    for (char c : s2)
    {
        b2.push_back(c - '0');
    }
}

bool bfs()
{
    queue<pair<int, int>> q;
    q.push(make_pair(0, 1));
    visited1[0] = 1;

    int cnt = 0;

    while (!q.empty())
    {
        int size = q.size();
        cnt++; // tiles at index 'cnt' on both bridges will be destroyed

        // needs to loop through until the starting size decreases to 0 at least
        // so they separately expand
        while (size--)
        {
            int pos = q.front().first;
            int bridge = q.front().second;
            q.pop();

            if (pos + 1 >= n || pos + k >= n)
            {
                return true;
            }

            if (bridge == 1)
            {
                if (!visited1[pos + 1] && (pos + 1) < n && b1[pos + 1] == 1)
                {
                    q.push(make_pair(pos + 1, 1));
                    visited1[pos + 1] = 1;
                }
                if (!visited1[pos - 1] && (pos - 1) > cnt && b1[pos - 1] == 1)
                {
                    q.push(make_pair(pos - 1, 1));
                    visited1[pos - 1] = 1;
                }
                if (!visited2[pos + k] && pos + k < n && b2[pos + k] == 1)
                {
                    q.push(make_pair(pos + k, 2));
                    visited2[pos + k] = 1;
                }
            }
            else
            {
                if (!visited2[pos + 1] && (pos + 1) < n && b2[pos + 1] == 1)
                {
                    q.push(make_pair(pos + 1, 2));
                    visited2[pos + 1] = 1;
                }
                if (!visited2[pos - 1] && (pos - 1) > cnt && b2[pos - 1] == 1)
                {
                    q.push(make_pair(pos - 1, 2));
                    visited2[pos - 1] = 1;
                }
                if (!visited1[pos + k] && pos + k < n && b1[pos + k] == 1)
                {
                    q.push(make_pair(pos + k, 1));
                    visited1[pos + k] = 1;
                }
            }
        }
    }
    return false;
}

int main()
{
    input();

    if (bfs())
    {
        cout << 1;
    }
    else
    {
        cout << 0;
    }
}