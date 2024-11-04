#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int height, width;
    cin >> height >> width;

    vector<string> curtain(height);
    for (int i = 0; i < height; i++)
    {
        cin >> curtain[i];
    }

    int pn;
    cin >> pn;
    vector<string> pattern(pn);
    for (int i = 0; i < pn; i++)
    {
        cin >> pattern[i];
    }

    bool found = false;
    for (int i = 0; i <= height - pn; i++)
    {
        for (int j = 0; j <= width - pn; j++)
        {
            bool match = true;

            for (int p = 0; p < pn; p++)
            {
                if (curtain[i + p].substr(j, pn) != pattern[p])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                cout << i << "," << j << endl;
                found = true;
            }
        }
    }
}