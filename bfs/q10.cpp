#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, k;
vector<int> b1;
vector<int> b2;
int visited1[100001];
int visited2[100001];
int cnt = 0;
int ans = 0;

void input()
{
    freopen("input.txt", "r", stdin);
    cin >> n >> k;

    string s;
    cin >> s;
    string s2;
    cin >> s2;

    int idx = 1;
    for (char c : s)
    {
        b1.push_back(c - '0' + 1);
        idx++;
    }

    idx = 1;
    for (char c : s2)
    {
        b2.push_back(c - '0' + 1);
        idx++;
    }
}

void bfs(int start)
{
    queue<pair<int, int>> q;
    q.push(make_pair(start, 1));

    while (!q.empty())
    {
        pair<int, int> now = q.front();
        q.pop();

        if (cnt > n)
        {
            ans = 1;
            return;
        }

        int pos_same[] = {now.first + 1, now.first - 1, now.first + k};

        for (int i = 0; i < sizeof(pos_same) / sizeof(pos_same[0]); ++i)
        {
            if (now.second == 1)
            {
                if (pos_same[i] >= 0 && b1[pos_same[i]] == 1 && !visited1[pos_same[i]])
                {
                    q.push(make_pair(pos_same[i], 1));
                    visited1[pos_same[i]] = 1;
                    if (pos_same[i] > 0)
                    {
                        b1[now.first] = 0;
                        b2[now.first] = 0;
                    }
                    if (i == 0)
                    {
                        cnt++;
                    }
                    else if (i == 1)
                    {
                        cnt--;
                    }
                }
                if (pos_same[i] >= 0 && b2[pos_same[i]] == 1 && !visited2[pos_same[i]])
                {
                    q.push(make_pair(pos_same[i], 2));
                    visited2[pos_same[i]] = 1;
                    if (pos_same[i] > 0)
                    {
                        b1[now.first] = 0;
                        b2[now.first] = 0;
                    }
                    cnt += k;
                }
            }
            else if (now.second == 2)
            {
                if (pos_same[i] >= 0 && b2[pos_same[i]] == 1 && !visited2[pos_same[i]])
                {
                    q.push(make_pair(pos_same[i], 2));
                    visited2[pos_same[i]] = 1;
                    if (pos_same[i] > 0)
                    {
                        b1[now.first] = 0;
                        b2[now.first] = 0;
                    }
                    if (i == 0)
                    {
                        cnt++;
                    }
                    else if (i == 1)
                    {
                        cnt--;
                    }
                }
                if (pos_same[i] >= 0 && b1[pos_same[i]] == 1 && !visited1[pos_same[i]])
                {
                    q.push(make_pair(pos_same[i], 1));
                    visited1[pos_same[i]] = 1;
                    if (pos_same[i] > 0)
                    {
                        b1[now.first] = 0;
                        b2[now.first] = 0;
                    }
                    cnt += k;
                }
            }
        }
    }
}

int main()
{
    input();

    bfs(-1);

    cout << ans;
}