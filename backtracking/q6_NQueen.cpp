#include <iostream>

using namespace std;

int n;
int board[14][14];
int cnt = 0;

int col[14];
int leftD[28];
int rightD[28];

void go(int num, int i)
{
    if (num >= n)
    {
        cnt++;
        return;
    }

    for (int j = 0; j < n; j++)
    {
        // // only works in python
        // if (col[j] || leftD[i - j] || rightD[i + j])
        //     continue;

        // col[j] = 1;
        // leftD[i - j] = 1;
        // rightD[i + j] = 1;
        // go(num + 1, i + 1);
        // col[j] = 0;
        // leftD[i - j] = 0;
        // rightD[i + j] = 0;

        int mkpos = n - 1;

        if (col[j] || leftD[i - j + mkpos] || rightD[i + j])
            continue;

        col[j] = 1;
        leftD[i - j + mkpos] = 1;
        rightD[i + j] = 1;
        go(num + 1, i + 1);
        col[j] = 0;
        leftD[i - j + mkpos] = 0;
        rightD[i + j] = 0;
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> n;

    go(0, 0);

    cout << cnt << '\n';
    return 0;
}

// #################### 강사님 코드 ###############################
#include <iostream>
using namespace std;

// index = row
// value = have you used it?
int DAT[20];
// index = / diagonal
// value = have you used it?
int LDRU[100];
// index = \ diagonal
// value = have you used it?
int LURD[100];

int N;
int cnt = 0;

void func(int row)
{
    if (row == N)
    {
        cnt++;
        return;
    }
    for (int col = 0; col < N; col++)
    {
        if (DAT[col] || LDRU[col + row] || LURD[col - row + N])
            continue;

        DAT[col] = 1;            // row번 행에서 col번 열에 queen 둔다
        LDRU[col + row] = 1;     // / 방향 대각선에 queen이 있다.
        LURD[col - row + N] = 1; // \ 방향 대각선에 queen이 있다.

        func(row + 1); // 다음 행에 queen을 둬본다

        DAT[col] = 0;            // row번 행에서 col번에 두었던 queen을 복구
        LDRU[col + row] = 0;     // / 방향 대각선에 둔 queen을 복구
        LURD[col - row + N] = 0; // \ 방향 대각선에 둔 queen을 복구
    }
}

int main()
{
    cin >> N;
    func(0); // 0번 행부터 시작
    cout << cnt;
}