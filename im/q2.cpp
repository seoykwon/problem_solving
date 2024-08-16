#include <iostream>
#include <climits>

using namespace std;

int t, n, m;
int answer[41];

int student[30][40];
int store[30][40] = {
    0,
};
int score[30] = {
    0,
};
int order = 1;

int main()
{
    // freopen("input.txt", "r", stdin);

    cin >> t;

    while (t--)
    {
        int maxScore = 0;
        int minScore = INT_MAX;
        cin >> n >> m;

        for (int i = 0; i < m; i++)
        {
            cin >> answer[i];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> student[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                store[i][j] = 0;
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (answer[j] == student[i][j])
                {
                    if (j == 0)
                    {
                        store[i][j] = 1;
                        continue;
                    }
                    store[i][j] = store[i][j - 1] + 1;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            score[i] = 0;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                score[i] += store[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (score[i] > maxScore)
            {
                maxScore = score[i];
            }
            if (score[i] < minScore)
            {
                minScore = score[i];
            }
        }

        // cout << "max" << maxScore << " min " << minScore << endl;

        cout << "#" << order << " ";
        cout << maxScore - minScore << endl;

        order++;
    }
}

// 배열 초기화를 해주지 않으면 예상치 못한 결과가 발생할 수 있다. 무조건 초기화를 해주도록!