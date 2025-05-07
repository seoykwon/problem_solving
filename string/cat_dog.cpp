#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int N;

string convert(string sentence)
{
    string ans = "";
    int sz = sentence.size();

    for (int i = 0; i < sz;)
    {
        if (sentence[i] == 'c')
        {
            int j = i + 1;
            // 숫자 스킵
            while (j < sz && isdigit(sentence[j]))
                j++;
            if (j < sz && sentence[j] == 'a')
            {
                j++;
                while (j < sz && isdigit(sentence[j]))
                    j++;
                if (j < sz && sentence[j] == 't')
                {
                    // "c[숫자]a[숫자]t" 패턴 찾음
                    ans += "dog";
                    i = j + 1;
                    continue;
                }
            }
        }
        if (sentence[i] == 'd')
        {
            int j = i + 1;
            while (j < sz && isdigit(sentence[j]))
                j++;
            if (j < sz && sentence[j] == 'o')
            {
                j++;
                while (j < sz && isdigit(sentence[j]))
                    j++;
                if (j < sz && sentence[j] == 'g')
                {
                    // "c[숫자]a[숫자]t" 패턴 찾음
                    ans += "cat";
                    i = j + 1;
                    continue;
                }
            }
        }
        // 패턴 아니면 그냥 추가
        ans += sentence[i];
        i++;
    }
    return ans;
}
// string convert(string sentence)
//{
//     string ans = "";
//     int sz = sentence.size();
//
//     for (int i = 0; i < sz; i++)
//     {
//         if (sentence[i] == 'c')
//         {
//             char nextch = 'a';
//             bool flag = false;
//             bool flag2 = false;
//             for (int j = i + 1; j < n; j++)
//             {
//                 if (sentence[j] >= '0' && sentence[j] <= '9')
//                     continue;
//                 if (sentence[j] == nextch && !flag)
//                 {
//                     nextch = 't';
//                     flag = true;
//                     continue;
//                 }
//                 if (sentence[j] == nextch && flag)
//                 {
//                     flag2 = true;
//                     ans += "dog";
//                     i = j + 1;
//                     break;
//                 }
//             }
//             if (flag2)
//                 continue;
//         }
//         else if (sentence[i] == 'd')
//         {
//         }
//         ans += sentence[i];
//     }
//     return ans;
// }

int main()
{
    freopen("input.txt", "r", stdin);
    string str;

    cin >> N;
    cin.ignore();

    for (int i = 0; i < N; i++)
    {
        getline(cin, str);

        string ans = convert(str);

        cout << ans << '\n';
    }
}