#include <iostream>
#include <string>
using namespace std;

int count(string str);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    cout << count(s);
    return 0;
}

int count(string str)
{
    string alphabet[8] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};

    for (int i = 0; i < 8; i++)
    {
        while (1)
        {
            if (str.find(alphabet[i]) != -1)
            {
                str.replace(str.find(alphabet[i]), alphabet[i].length(), "#");
            }
            else
                break;
        }
    }
    return str.length();
}