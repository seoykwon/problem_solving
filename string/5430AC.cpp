#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
using namespace std;

int testCase;
deque<int> d;
string ACS, arrString;
int arrCount;

int main()
{
    ios_base::sync_with_stdio();
    cin.tie(0);

    cin >> testCase;

    for (int t = 0; t < testCase; t++)
    {
        d.clear();
        cin >> ACS;
        cin >> arrCount;
        cin >> arrString;
        int num = 0;

        for (int i = 0; i < arrString.size(); i++)
        {
            if (arrString[i] == '[' || arrString[i] == ']')
                continue;

            if (arrString[i] == ',')
            {
                d.push_back(num);
                num = 0;
            }

            else
            {
                num = num * 10 + arrString[i] - '0';
            }
        }
        if (num != 0)
        {
            d.push_back(num);
        }

        bool isError = false, isReverse = false;
        for (int i = 0; i < ACS.size(); i++)
        {
            if (ACS[i] == 'R')
            {
                if (isReverse)
                    isReverse = false;
                else
                    isReverse = true;
            }
            else if (ACS[i] == 'D')
            {
                if (d.empty())
                {
                    isError = true;
                    break;
                }

                if (isReverse)
                {
                    d.pop_back();
                }
                else
                {
                    d.pop_front();
                }
            }
        }

        if (isReverse && !isError)
        {
            reverse(d.begin(), d.end());
        }

        if (isError)
        {
            cout << "error";
        }
        else
        {
            cout << "[";
            for (int i = 0; i < d.size(); i++)
            {
                if (i == d.size() - 1)
                {
                    cout << d[i];
                }
                else
                {
                    cout << d[i] << ",";
                }
            }
            cout << "]";
        }
        cout << "\n";
    }
}