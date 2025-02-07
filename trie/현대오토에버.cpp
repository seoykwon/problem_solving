/**
 * HMG는 현대자동차그룹의 약자이다. 현대자동차그룹(HMG)는 완성차인 현대자동차와 기아를 포함하여 6개의 사업 영역 (완성차, 철강, 건설, 부품, 금융, 기타)의 다양한 계열사를 포함하는 명칭이다.

보통은 현대자동차그룹을 HMG라고 줄여서 부른다.
이처럼 긴 단어를 한번에 쉽게 부르기 위한 약자들이 존재한다.

예를 들면, 현대자동차(Hyundai-Motor-Company)는 HMC로 줄일 수 있다.

회사들의 명칭을 줄여서 부르는 규칙은 다음과 같다.
1. 단어의 첫 글자인 대문자를 조합하여 부른다.
2. 그 대문자들을 순서대로 작성하면 '약자(Abbreviation)'가 된다.
3. 이렇게 부르기 길어서 힘든 회사명을 위와 같은 규칙을 통해 약자로 만들어 주는 프로그램을 작성해 보자.

제약조건
첫 번째 글자는 항상 대문자이고, 하이픈(-) 뒤에는 반드시 대문자이다. 그 외의 모든 문자는 소문자이다.

입력형식
입력은 한 줄로 이루어져 있고, 최대 100글자의 영어 알파벳 대문자, 소문자, 그리고 하이픈(-) 으로만 이루어져 있다.

출력형식
첫 번째 줄에 회사의 약자를 출력한다.

입력 예시 1
Hyundai-Motor-Group
출력 예시 1
HMG

입력 예시 2
Next-Generation-Vehicle
출력 예시 2
NGV
 */

#include <iostream>
#include <sstream>

int main()
{
    std::string input, abbreviation;
    std::cin >> input;

    // 첫 번째 글자는 무조건 대문자이므로 추가
    abbreviation += input[0];

    // '-' 뒤에 오는 대문자를 찾아 추가
    for (size_t i = 1; i < input.size(); i++)
    {
        if (input[i] == '-' && i + 1 < input.size())
        {
            abbreviation += input[i + 1];
        }
    }

    std::cout << abbreviation << std::endl;
    return 0;
}

/**
 * 📌 문제 변형
여러 개의 회사명을 저장한다.
각 회사명의 약자를 자동으로 생성하여 트라이에 저장한다.
사용자가 약자를 입력하면 해당 약자의 원래 회사명을 찾아 출력한다.

 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children;
    vector<string> companyNames; // 해당 약자로 검색 가능한 회사 목록
};

class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    // 약자 생성 함수
    string generateAbbreviation(const string &company)
    {
        string abbreviation;
        abbreviation += company[0]; // 첫 번째 대문자 추가
        for (size_t i = 1; i < company.size(); i++)
        {
            if (company[i] == '-' && i + 1 < company.size())
            {
                abbreviation += company[i + 1]; // '-' 뒤 대문자 추가
            }
        }
        return abbreviation;
    }

    // 트라이에 약자 및 원본 회사명을 추가
    void insert(const string &company)
    {
        string abbr = generateAbbreviation(company);
        TrieNode *node = root;
        for (char c : abbr)
        {
            if (!node->children.count(c))
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->companyNames.push_back(company);
    }

    // 약자로 회사명 검색
    vector<string> search(const string &abbr)
    {
        TrieNode *node = root;
        for (char c : abbr)
        {
            if (!node->children.count(c))
            {
                return {}; // 약자가 존재하지 않음
            }
            node = node->children[c];
        }
        return node->companyNames;
    }
};

int main()
{
    Trie trie;
    vector<string> companies = {
        "Hyundai-Motor-Group",
        "Hyundai-Motor-Company",
        "Next-Generation-Vehicle",
        "Samsung-Electronics",
        "Seoul-National-University"};

    // 트라이에 회사명 추가
    for (const string &company : companies)
    {
        trie.insert(company);
    }

    // 사용자 입력
    string query;
    cout << "검색할 약자를 입력하세요: ";
    cin >> query;

    // 검색 결과 출력
    vector<string> results = trie.search(query);
    if (!results.empty())
    {
        cout << "해당 약자로 검색된 회사 목록:\n";
        for (const string &name : results)
        {
            cout << "- " << name << endl;
        }
    }
    else
    {
        cout << "해당 약자로 등록된 회사가 없습니다.\n";
    }

    return 0;
}
