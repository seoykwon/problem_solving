#include <iostream>
#include <string>
#include <cctype> // tolower
using namespace std;

string to_lowercase(const string &s)
{
    string res = s;
    for (char &c : res)
    {
        c = tolower(c);
    }
    return res;
}

string replace_cat_dog(string input)
{
    string lower = to_lowercase(input);
    string result;
    int i = 0;

    while (i < input.size())
    {
        if (i + 2 < input.size())
        { // 최소 3글자 필요
            string sub = lower.substr(i, 3);
            if (sub == "cat")
            {
                result += "dog";
                i += 3;
                continue;
            }
            else if (sub == "dog")
            {
                result += "cat";
                i += 3;
                continue;
            }
        }
        // 그냥 복사
        result += input[i];
        i++;
    }

    return result;
}

int main()
{
    string input;
    getline(cin, input);

    string output = replace_cat_dog(input);
    cout << output << endl;
    return 0;
}
