#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 사용자 정의 비교 함수
bool cmp(string a, string b)
{
    return a + b > b + a;
}

string solution(vector<int> numbers)
{
    // 숫자를 문자열로 변환
    vector<string> strn;
    for (int number : numbers)
    {
        strn.push_back(to_string(number));
    }

    // 사용자 정의 비교 함수로 정렬
    sort(strn.begin(), strn.end(), cmp);

    // 정렬 후 결과를 하나의 문자열로 결합
    string answer;
    for (auto numStr : strn)
    {
        answer += numStr;
    }

    // 만약 가장 큰 수가 "0"으로 시작하면 "0" 반환
    if (answer[0] == '0')
    {
        return "0";
    }

    return answer;
}