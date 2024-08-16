#include <iostream>
#include <queue>

using namespace std;

int n;
int board[6][6];

struct place
{
    char start;
    char dest;
    int price;
};

struct cmp
{
    bool operator()(place a, place b)
    {
        return a.price < b.price;
    }
};

priority_queue<place, vector<place>, cmp> pq;

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
            if (board[i][j] > 0)
            {
                char from = 'A' + i;
                char to = 'A' + j;
                place tmp = {from, to, board[i][j]};
                pq.push(tmp);
            }
        }
    }

    int size = 3;
    while (size--)
    {
        place tmp = pq.top();
        pq.pop();

        cout << tmp.start << "-" << tmp.dest << " " << tmp.price << endl;
    }
}