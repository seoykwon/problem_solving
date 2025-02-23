#include <iostream>
#include <vector>
#include <cmath>
#define NM 2005

using namespace std;

const int HASH_SIZE = pow(2, 30) - 1;

int H, W, N, M;
int targetArr[NM][NM], originArr[NM][NM], horizonHashArr[NM][NM], verticalHashArr[NM][NM];

int getMaxPower(int len, int shift)
{
    long long result = 1;
    for (int i = 0; i < len - 1; i++)
    {
        result = (result << shift) + result;
    }
    return (int)(result & HASH_SIZE);
}

int getHorizonHash(int matrix[][NM], int len, int row, int col)
{
    long long result = 0;
    for (int i = 0; i < len; i++)
    {
        result = (result << 4) + result + matrix[row][col + i];
    }
    return (int)(result & HASH_SIZE);
}

int getVerticalHash(int matrix[][NM], int len, int row, int col)
{
    long long result = 0;
    for (int i = 0; i < len; i++)
    {
        result = (result << 5) + result + matrix[row + i][col];
    }
    return (int)(result & HASH_SIZE);
}

int getNext(int prev, int del, int maxPower, int add, int shift)
{
    long long result = prev - (del * maxPower);
    result = (result << shift) + result + add;
    return (int)(result & HASH_SIZE);
}

void getHashArr(int matrix[][NM], int matrix_height, int matrix_width, int pattern_height, int pattern_width)
{
    int rowMaxP = getMaxPower(pattern_height, 5);
    int colMaxP = getMaxPower(pattern_width, 4);

    for (int i = 0; i < matrix_height; i++)
    {
        int hash = getHorizonHash(matrix, pattern_width, i, 0);
        horizonHashArr[i][0] = hash;

        for (int j = 1; j <= matrix_width - pattern_width; j++)
        {
            horizonHashArr[i][j] = getNext(hash, matrix[i][j - 1], colMaxP, matrix[i][j - 1 + pattern_width], 4);
            hash = horizonHashArr[i][j];
        }
    }

    for (int j = 0; j <= matrix_width - pattern_width; j++)
    {
        int hash = getVerticalHash(horizonHashArr, pattern_height, 0, j);
        verticalHashArr[0][j] = hash;

        for (int i = 1; i <= matrix_height - pattern_height; i++)
        {
            verticalHashArr[i][j] = getNext(hash, horizonHashArr[i - 1][j], rowMaxP, horizonHashArr[i - 1 + pattern_height][j], 5);
            hash = verticalHashArr[i][j];
        }
    }
}

int solution(int targetArr[][NM], int originArr[][NM])
{
    getHashArr(targetArr, H, W, H, W);
    int hashVal = verticalHashArr[0][0];
    getHashArr(originArr, N, M, H, W);

    int cnt = 0;
    for (int i = 0; i <= N - H; i++)
    {
        for (int j = 0; j <= M - W; j++)
        {
            cnt = verticalHashArr[i][j] == hashVal ? cnt + 1 : cnt;
        }
    }

    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int testCase = 1; testCase <= T; testCase++)
    {
        cin >> H >> W >> N >> M;

        for (int i = 0; i < H; i++)
        {
            string str;
            cin >> str;
            for (int j = 0; j < W; j++)
            {
                targetArr[i][j] = str[j] == 'o' ? 1 : 0;
            }
        }

        for (int i = 0; i < N; i++)
        {
            string str;
            cin >> str;
            for (int j = 0; j < M; j++)
            {
                originArr[i][j] = str[j] == 'o' ? 1 : 0;
            }
        }

        cout << "#" << testCase << " " << solution(targetArr, originArr) << "\n";
    }

    return 0;
}
