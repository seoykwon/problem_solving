#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        int n, m, tgtIdx;
        cin >> n >> m >> tgtIdx;

        list<int> linkedList;

        for (int i = 0; i < n; i++)
        {
            int num;
            cin >> num;
            linkedList.push_back(num);
        }

        for (int i = 0; i < m; i++)
        {
            string cmd;
            cin >> cmd;

            if (cmd == "I")
            {
                int x, y;
                cin >> x >> y;

                auto it = linkedList.begin();
                advance(it, x);
                linkedList.insert(it, y);
            }
            else if (cmd == "D")
            {
                int x;
                cin >> x;

                auto it = linkedList.begin();
                advance(it, x);
                linkedList.erase(it);
            }
            else if (cmd == "C")
            {
                int x, y;
                cin >> x >> y;

                auto it = linkedList.begin();
                advance(it, x);
                *it = y;
            }
        }

        if (linkedList.size() > tgtIdx)
        {
            auto it = linkedList.begin();
            advance(it, tgtIdx);
            cout << "#" << tc << " " << *it << "\n";
        }
        else
        {
            cout << "#" << tc << " " << -1 << "\n";
        }
    }
}

// #############################################
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#define NM 100005

using namespace std;

string X;
int n, Q, L;
struct NODE
{
    int v;
    NODE *prev;
    NODE *next;
    NODE() {}
    NODE(int v, NODE *prev, NODE *next) : v(v), prev(prev), next(next) {}
} *head;
int cnt;

void input()
{
    cin >> n >> Q >> L;
    NODE *cur = head;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (i == 1)
        {
            head = new NODE(x, 0, 0);
            cur = head;
        }
        else
        {
            cur->next = new NODE(x, cur, 0);
            cur = cur->next;
        }
        cnt++;
    }
}

void pro()
{
    while (Q--)
    {
        char ch;
        cin >> ch;
        if (ch == 'C')
        {
            NODE *cur = head;
            int y, s;
            cin >> y >> s;
            for (int i = 1; i <= y; i++)
            {
                cur = cur->next;
            }
            cur->v = s;
        }
        else if (ch == 'I')
        {
            int x, y;
            cin >> x >> y;
            x--;

            if (x == -1)
            {
                if (cnt > 0)
                {
                    NODE *newNode = new NODE(y, 0, head);
                    head->prev = newNode;
                    head = newNode;
                }
                else
                    head = new NODE(y, 0, 0);
            }
            else
            {
                NODE *cur = head;
                while (x--)
                    cur = cur->next;
                NODE *node = new NODE(y, cur, cur->next);
                if (cur->next)
                    cur->next->prev = node;
                cur->next = node;
            }
            cnt++;
        }
        else if (ch == 'D')
        {
            int x;
            cin >> x;
            NODE *cur = head;
            while (x--)
                cur = cur->next;
            NODE *prev = cur->prev, *next = cur->next;
            if (prev)
                prev->next = next;
            if (next)
                next->prev = prev;
            if (prev == NULL)
                head = next;
            cnt--;
        }
    }
    NODE *cur = head;
    for (int i = 1; i <= L; i++)
    {
        if (cur == NULL)
            break;
        cur = cur->next;
    }
    if (cur == NULL)
        cout << -1 << "\n";
    else
        cout << cur->v << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int TT;
    cin >> TT;
    for (int tt = 1; tt <= TT; tt++)
    {
        input();
        cout << "#" << tt << " ";
        pro();
    }
    return 0;
}