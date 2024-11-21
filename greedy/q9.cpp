#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<string> words;
vector<string> nums;
unordered_map<char, int> mp;

int main()
{
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;

        words.push_back(tmp);
        nums.push_back("");
    }

    int longest = 0;
    for (int i = 0; i < n; i++)
    {
        int sz = words[i].size();
        longest = max(longest, sz);
    }

    for (int i = 0; i < n; i++)
    {
        if (words[i].size() < longest)
        {
            int diff = longest - words[i].size();
            string space = "";
            for (int j = 0; j < diff; j++)
            {
                space += " ";
            }

            string newStr = space + words[i];

            words[i] = newStr;
        }
    }

    int cnt = 9;
    for (int i = 0; i < longest; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char cur = words[j][i];

            if (cur == ' ')
                continue;

            if (mp.find(cur) == mp.end())
            {
                mp.insert({cur, cnt});
                nums[j] += to_string(cnt);
                cnt--;
            }
            else
            {
                nums[j] += to_string(mp.at(cur));
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += stoi(nums[i]);
    }

    cout << sum << '\n';

    return 0;
}

// ########## above is wrong bc i did not calculate the importance of each alphabet ###############
/**
 * 문제의 핵심
알파벳에 숫자를 할당하는 방식은 여러 가지가 있을 수 있는데, 중요한 점은 자주 등장하는 알파벳에 더 큰 숫자를 배정하는 것입니다.
예를 들어, AB와 BB라는 두 단어가 있을 때, B가 두 번 등장하므로 B에는 더 큰 숫자를 할당해야 합니다.
문제 해결 전략
각 알파벳의 중요도 계산:

각 알파벳이 등장하는 위치(십의 자리, 백의 자리 등)에 따라 그 알파벳의 중요도를 계산합니다.
예를 들어, AB와 BB에서 B는 두 번 등장하고, A는 한 번 등장하므로 B가 더 중요한 알파벳이 됩니다.
중요도에 따라 알파벳에 숫자 할당:

중요도가 높은 알파벳에 큰 숫자를 할당하여 합을 최대로 만듭니다.
알파벳에 숫자를 할당하는 순서:

중요도가 높은 알파벳에 큰 숫자를 할당하는 방법으로 알파벳의 중요도를 구하고, 그 순서대로 9부터 0까지 숫자를 할당합니다.
알고리즘
각 알파벳의 중요도 계산: 각 자리에 등장하는 알파벳의 자릿수 값을 계산합니다.
우선순위 계산: 중요도에 따라 알파벳을 정렬합니다.
숫자 할당: 가장 중요한 알파벳부터 큰 숫자를 할당합니다.
합 계산: 각 단어를 숫자로 변환하여 합을 구합니다.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Alphabet
{
    char ch;
    int value;
};

int main()
{
    int n;
    cin >> n;

    vector<string> words(n);
    unordered_map<char, int> letterImportance;

    for (int i = 0; i < n; i++)
    {
        cin >> words[i];
    }

    // 각 알파벳의 자릿수에 따른 중요도 계산
    for (const auto &word : words)
    {
        int length = word.length();
        for (int i = 0; i < length; i++)
        {
            char ch = word[i];
            // 10의 자리, 100의 자리, ... 자릿수에 따라 중요도 증가
            letterImportance[ch] += pow(10, length - i - 1);
        }
    }

    // 중요도 계산 후 알파벳을 중요도에 따라 내림차순으로 정렬
    vector<Alphabet> alphabets;
    for (const auto &entry : letterImportance)
    {
        alphabets.push_back({entry.first, entry.second});
    }

    sort(alphabets.begin(), alphabets.end(), [](const Alphabet &a, const Alphabet &b)
         {
             return a.value > b.value; // 중요도가 큰 순으로 정렬
         });

    // 숫자 할당
    unordered_map<char, int> letterToDigit;
    int digit = 9;
    for (const auto &alphabet : alphabets)
    {
        letterToDigit[alphabet.ch] = digit--;
    }

    // 숫자 할당 후 각 단어를 숫자로 바꾸기
    int totalSum = 0;
    for (const auto &word : words)
    {
        int number = 0;
        for (char ch : word)
        {
            number = number * 10 + letterToDigit[ch];
        }
        totalSum += number;
    }

    // 결과 출력
    cout << totalSum << endl;

    return 0;
}

// ####################### 강사님 코드 ############################
#include <iostream>
#include <algorithm>
using namespace std;

int n;
string words[10];
int DAT[26];

bool cmp(int a, int b)
{
    if (a > b)
        return true;
    if (a < b)
        return false;
    return false;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> words[i];
        int len = 1;

        // 앞에 오는 순서대로 기록
        // 예: ABC
        // A : 100
        // B : 10
        // C : 1
        for (int j = 0; j < words[i].length() - 1; j++)
            len *= 10;

        for (int j = 0; j < words[i].length(); j++)
        {
            DAT[words[i][j] - 'A'] += len;
            len /= 10;
        }
    }

    // 내림차순으로 정렬
    sort(DAT, DAT + 26, cmp);

    // 가장 큰 값에 9부터 곱해서 더할 것
    int score = 9;
    int ans = 0;
    for (int i = 0; i < 10; i++)
    {
        ans += DAT[i] * score;
        score--;
    }
    cout << ans;
}