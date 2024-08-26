#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int Q;
int num[10001];

struct cmp
{
    bool operator()(int a, int b)
    {
        if (a > b)
            return true;
        if (a < b)
            return false;
        return false;
    }
};

priority_queue<int, vector<int>, cmp> pq;

void input()
{
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        cin >> num[i];
    }
}

int main()
{
    input();

    pq.push(1);

    for (int i = 2; i <= num[Q - 1]; i++)
    {
        check(i);
    }

    for (int i = 0; i < Q; i++)
    {
        cout << pq[i] << " ";
    }
}