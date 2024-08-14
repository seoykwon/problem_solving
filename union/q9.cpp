#include <iostream>

using namespace std;

int board[100][100] = {
    0,
};
int parent[10000];
int n;
int sum_group = 0;
int sum_size = 0;
int cnt[10000];

struct island
{
    int y;
    int x;
};

island lst[10000];

int Find(int a)
{
    if (a == parent[a])
    {
        return a;
    }
    return parent[a] = Find(parent[a]);
}

void Union(int a, int b)
{
    int rootA = Find(a);
    int rootB = Find(b);

    if (rootA == rootB)
    {
        return;
    }

    parent[rootB] = rootA;
}

// 가로 10칸, 세로 12칸이다
// int board[14][12];
// (1,1) ~ (10,12)
//   1111
//   1001
//   1001
//   1111

//  2*n + 1 // 10101010100 -> 짝수
// -> (2*n)|1 // 10101010101 -> 홀수
// -> (n<<1)|1

// 3216545646 <- 부모입장에서 왼쪽자식일까 오른쪽자식일까 -> 321.. &1
// n/2 => 부모
// = n>>1

int ydir[4] = {1, 0, -1, 0};
int xdir[4] = {0, -1, 0, 1};

void check(int row, int col)
{

    for (int i = 0; i < 4; i++)
    {
        int ny = row + ydir[i];
        int nx = col + xdir[i];

        // if (ny >= 0 && ny < 100 && nx >= 0 && nx < 100)
        if (ny < 0 || ny >= 100 || nx < 0 || nx >= 100)
            continue;

        int tmp = board[ny][nx];

        if (tmp == 0)
            continue;
        Union(tmp, board[row][col]);
    }
}

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        parent[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {

        int col, row;
        cin >> row >> col;

        lst[i] = {row, col};

        board[row][col] = i;
        parent[i] = i;

        check(row, col);

        int max = 0;
        int group = 0;

        for (int j = 1; j <= n; j++)
        {
            cnt[j] = 0;
        }

        for (int j = 1; j <= n && j <= i; j++)
        {
            cnt[Find(parent[j])]++;
        }

        // cout << i << "'s group : " << group << endl;

        for (int j = 1; j <= n; j++)
        {
            // cout << "cnt of j : " << cnt[j] << endl;
            if (cnt[j] > 0)
            {
                group++;
            }
            if (cnt[j] > max)
            {
                max = cnt[j];
            }
        }

        // cout << i << "'s group : " << group << endl;
        sum_group += group;
        sum_size += max;
    }
    cout << sum_group << endl;
    cout << sum_size << endl;
}

// row, col ordering
// index problem
// first initialization consisted of 0's
// but the very first element's value = 0
// so it appears as it no change
// changed the staring index value from 0 to 1
// board[row][col] = i;
// the "i" value needs to start from 1