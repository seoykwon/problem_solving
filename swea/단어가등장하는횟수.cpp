// 돈이 되는 알고리즘
// 롤링 해쉬, 로빈 카프 rolling hash
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int EXPONENT1 = 32;
const int EXPONENT2 = 37;
const int EXPONENT3 = 41;

int getCount(const string &str, const string &pattern)
{
    int count = 0;

    int stringLength = str.length();
    int patternLength = pattern.length();

    int stringHash1 = 0;
    int patternHash1 = 0;

    int stringHash2 = 0;
    int patternHash2 = 0;

    int stringHash3 = 0;
    int patternHash3 = 0;

    int power1 = 1;
    int power2 = 1;
    int power3 = 1;

    for (int i = 0; i <= stringLength - patternLength; i++)
    { // Window's starting position
        // Check if string[i ... i + patternLength - 1] is equal to pattern
        if (i == 0)
        {
            for (int j = 0; j < patternLength; j++)
            {
                stringHash1 += str[patternLength - 1 - j] * power1;
                patternHash1 += pattern[patternLength - 1 - j] * power1;

                stringHash2 += str[patternLength - 1 - j] * power2;
                patternHash2 += pattern[patternLength - 1 - j] * power2;

                stringHash3 += str[patternLength - 1 - j] * power3;
                patternHash3 += pattern[patternLength - 1 - j] * power3;

                if (j < patternLength - 1)
                {
                    power1 *= EXPONENT1;
                    power2 *= EXPONENT2;
                    power3 *= EXPONENT3;
                }
            }
        }
        else
        {
            stringHash1 = EXPONENT1 * (stringHash1 - str[i - 1] * power1) + str[patternLength - 1 + i];
            stringHash2 = EXPONENT2 * (stringHash2 - str[i - 1] * power2) + str[patternLength - 1 + i];
            stringHash3 = EXPONENT3 * (stringHash3 - str[i - 1] * power3) + str[patternLength - 1 + i];
        }

        if (stringHash1 == patternHash1 && stringHash2 == patternHash2 && stringHash3 == patternHash3)
        {
            count++;
        }
    }

    return count;
}

int main()
{
    int T;
    cin >> T;
    cin.ignore();

    for (int tc = 1; tc <= T; tc++)
    {
        string B, S;
        getline(cin, B);
        getline(cin, S);

        int result = getCount(B, S);

        cout << "#" << tc << " " << result << "\n";
    }

    return 0;
}