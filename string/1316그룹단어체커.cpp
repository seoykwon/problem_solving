#include <iostream>
#include <string>
using namespace std;

int main()
{
    int num, cnt = 0;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        string str;
        cin >> str;
        int check = 0;

        for (int j = 0; j < str.length() - 1; j++)
        {
            if (str[j] != str[j + 1] && str.substr(j + 1).find(str[j]) != string::npos)
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
            cnt += 1;
    }
    cout << cnt << '\n';
    return 0;
}