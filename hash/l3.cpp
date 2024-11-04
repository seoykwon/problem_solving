#include <iostream>
#include <string>

using namespace std;

/*
npos는 C++에서 문자열 검색 함수(find, rfind 등)들이 특정 문자열이나 문자를 찾을 수 없을 때
반환하는 값입니다. npos는 std::string 클래스 내에 정의되어 있으며,
정확한 의미는 **"no position"**입니다. 보통 std::string::npos로 사용하며,
size_t 타입의 가장 큰 값으로 정의됩니다.
*/

int main()
{
    string text = "BOBOOBOBOBOBBM";

    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;

        int count = 0;
        size_t pos = text.find(word);

        while (pos != string::npos)
        {
            ++count;
            pos = text.find(word, pos + 1);
        }

        cout << count << endl;
    }

    return 0;
}