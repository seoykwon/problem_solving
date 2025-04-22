#include <iostream>
#include <string>
#include <sstream>
using namespace std;

typedef pair<int, int> pii;

int ground[51][51];
int N, Q;
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

struct status
{
    int y, x;
    int time;
};

int travel(int r1, int c1, int r2, int c2)
{
    pii loc = {r1, c1};

    // cannot land on (1) slimy rock
    // cannot pass over (2) cousin rock
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> N;
    cin.ignore();

    for (int i = 1; i <= N; i++)
    {
        string str;
        getline(cin, str);

        stringstream st(str);

        for (int j = 1; j <= N; j++)
        {
            char rock;
            st >> rock;
            int fin = 0;

            // safe rock
            if (rock == '.')
            {
                fin = 1;
            }

            // slimy rock
            else if (rock == 'S')
            {
                fin = -1;
            }

            // cousin rock
            else if (rock == '#')
            {
                fin = 2;
            }

            ground[i][j] = fin;
        }
    }

    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        int ans = travel(r1, c1, r2, c2);

        cout << ans << '\n';
    }
}