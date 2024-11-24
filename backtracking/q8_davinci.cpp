#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> tower;

void backtrack()
{
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    tower.resize(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> tower[i][j];
        }
    }

    // this is for debugging
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << tower[i][j] << ' ';
        }
        cout << '\n';
    }

    backtrack();

    return 0;
}