#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// 겹치지 않는지 확인하는 함수
bool is_unique_code(const string &candidate, const set<string> &codes)
{
    return codes.find(candidate) == codes.end(); // 겹치지 않으면 true
}

// 가장 짧은 겹치지 않는 지역 코드 찾기
vector<string> find_shortest_unique_code(const vector<string> &queries)
{
    vector<string> codes;
    set<string> used_codes; // 이미 사용된 지역 코드들을 기록하는 집합

    size_t max_length = 0;

    // 먼저 각 지역 이름에 대해 가능한 가장 짧은 코드 길이를 찾기 위해
    for (const auto &query : queries)
    {
        bool found = false;

        // 1글자부터 시작해서 점차 길이를 늘려가며 찾기
        for (size_t length = 1; length <= query.size(); ++length)
        {
            for (size_t start = 0; start <= query.size() - length; ++start)
            {
                string candidate = query.substr(start, length);
                if (is_unique_code(candidate, used_codes))
                {
                    codes.push_back(candidate);
                    used_codes.insert(candidate); // 사용된 코드로 추가
                    found = true;
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }
    }

    // 모든 지역 코드의 길이가 같아야 하므로, 가장 짧은 코드 길이를 구함
    size_t min_length = 0;
    for (const auto &code : codes)
    {
        min_length = max(min_length, code.size()); // 가장 긴 코드 길이를 찾음
    }

    // 모든 코드의 길이를 min_length로 맞추기
    // 만약 원본 문자열의 길이가 min_length보다 작으면 이제 _ 를 넣어주는 논리
    for (auto &code : codes)
    {
        if (code.size() < min_length)
        {
            code += string(min_length - code.size(), '_'); // 짧은 코드에 _ 추가
        }
    }

    return codes;
}

int main()
{
    // 예시 입력
    vector<string> queries = {"NETHERLAND", "NET", "NE"};

    // 결과 출력
    vector<string> codes = find_shortest_unique_code(queries);

    for (const auto &code : codes)
    {
        cout << code << endl;
    }

    return 0;
}

// #####################################################################

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

// TrieNode 정의
struct TrieNode
{
    unordered_map<char, TrieNode *> children;
    bool is_end_of_word; // 이 노드가 끝인지를 표시
    TrieNode() : is_end_of_word(false) {}
};

// Trie 정의
class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    // Trie에 단어 삽입
    bool insert(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            if (node->children.find(ch) == node->children.end())
            {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }

        if (node->is_end_of_word)
        {
            return false; // 이미 끝나는 단어가 존재하면 false 반환 (중복)
        }

        node->is_end_of_word = true; // 단어의 끝
        return true;                 // 성공적으로 삽입
    }

    // 부분 문자열을 넣을 수 있는지 확인 (겹치지 않으면 true)
    bool can_insert(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            if (node->children.find(ch) == node->children.end())
            {
                return true; // 없으면 넣을 수 있음
            }
            node = node->children[ch];
        }
        return !node->is_end_of_word; // 이미 끝나는 단어가 아니어야 함
    }
};

// 가장 짧은 겹치지 않는 지역 코드 찾기
vector<string> find_shortest_unique_code(const vector<string> &queries)
{
    Trie trie;
    vector<string> codes;

    // 각 지역 이름에 대해 가능한 가장 짧은 코드 길이를 찾기 위해
    for (const auto &query : queries)
    {
        bool found = false;

        // 1글자부터 시작해서 점차 길이를 늘려가며 찾기
        for (size_t length = 1; length <= query.size(); ++length)
        {
            if (found)
                break; // 이미 겹치지 않는 코드를 찾았으면 더 이상 검사하지 않음

            // 각 부분 문자열을 순차적으로 확인
            for (size_t start = 0; start <= query.size() - length; ++start)
            {
                string candidate = query.substr(start, length);

                // 겹치지 않으면 해당 부분 문자열을 사용
                if (trie.can_insert(candidate))
                {
                    codes.push_back(candidate);
                    trie.insert(candidate); // 사용된 코드로 추가
                    found = true;
                    break;
                }
            }
        }
    }

    // 모든 지역 코드의 길이가 같아야 하므로, 가장 긴 코드 길이를 구함
    size_t max_length = 0;
    for (const auto &code : codes)
    {
        max_length = max(max_length, code.size()); // 가장 긴 코드 길이를 찾음
    }

    // 모든 코드의 길이를 max_length로 맞추기
    for (auto &code : codes)
    {
        if (code.size() < max_length)
        {
            code += string(max_length - code.size(), '_'); // 짧은 코드에 _ 추가
        }
    }

    return codes;
}

int main()
{
    // 예시 입력
    vector<string> queries = {"NETHERLAND", "NET", "NE"};

    // 결과 출력
    vector<string> codes = find_shortest_unique_code(queries);

    for (const auto &code : codes)
    {
        cout << code << endl;
    }

    return 0;
}
