// #include <iostream>
// #include <vector>
// #include <unordered_map>
// using namespace std;

// class TrieNode
// {
// public:
//     unordered_map<char, TrieNode *> children;
//     int count = 0; // 해당 노드를 거치는 단어의 개수
// };

// class Trie
// {
// private:
//     TrieNode *root;

// public:
//     Trie()
//     {
//         root = new TrieNode();
//     }

//     // 트라이에 단어 삽입 및 접두사 등장 횟수 증가
//     void insert(const string &word)
//     {
//         TrieNode *node = root;
//         for (char c : word)
//         {
//             if (!node->children.count(c))
//             {
//                 node->children[c] = new TrieNode();
//             }
//             node = node->children[c];
//             node->count++;
//         }
//     }

//     // 특정 단어에 대한 최소한의 고유 길이 찾기
//     int findMinUniqueLength(const string &word)
//     {
//         TrieNode *node = root;
//         for (int i = 0; i < word.size(); i++)
//         {
//             node = node->children[word[i]];
//             if (node->count == 1)
//             {
//                 return i + 1; // 현재까지의 길이가 유일한 식별자로 충분함
//             }
//         }
//         return word.size(); // 마지막까지 겹치면 전체 단어 사용
//     }
// };

// // 고유 지역 코드 생성
// vector<string> generateRegionCodes(vector<string> &regions)
// {
//     Trie trie;
//     unordered_map<string, string> regionToCode;
//     vector<string> codes;

//     // 1. 트라이에 모든 지역 이름 삽입
//     for (const string &region : regions)
//     {
//         trie.insert(region);
//     }

//     // 2. 각 지역 이름의 최소한의 고유한 길이 찾기
//     int maxCodeLength = 1;
//     for (const string &region : regions)
//     {
//         int minLength = trie.findMinUniqueLength(region);
//         maxCodeLength = max(maxCodeLength, minLength);
//         regionToCode[region] = region.substr(0, minLength); // 초기 코드 설정
//     }

//     // 3. 모든 코드가 동일한 길이를 가지도록 패딩(_ 추가)
//     for (const string &region : regions)
//     {
//         string code = regionToCode[region];
//         while (code.size() < maxCodeLength)
//         {
//             code += "_";
//         }
//         codes.push_back(code);
//     }

//     return codes;
// }

// int main()
// {
//     vector<string> regions = {"ABC", "BERLIN", "DUTCH", "DAEGU", "CHEZH"};
//     vector<string> codes = generateRegionCodes(regions);

//     cout << "지역 코드: ";
//     for (const string &code : codes)
//     {
//         cout << code << " ";
//     }
//     cout << endl;

//     return 0;
// }

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children;
    int count = 0; // 해당 노드를 거치는 단어의 개수
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

    // 트라이에 단어 삽입 및 접두사 등장 횟수 증가
    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (!node->children.count(c))
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->count++;
        }
    }

    // 특정 단어에 대한 최소한의 고유 길이 찾기
    int findMinUniqueLength(const string &word)
    {
        TrieNode *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            node = node->children[word[i]];
            if (node->count == 1)
            {
                return i + 1; // 현재까지의 길이가 유일한 식별자로 충분함
            }
        }
        return word.size(); // 마지막까지 겹치면 전체 단어 사용
    }
};

// 고유 지역 코드 생성
vector<string> generateRegionCodes(vector<string> &regions)
{
    Trie trie;
    unordered_map<string, string> regionToCode;
    vector<string> codes;

    // 1. 트라이에 모든 지역 이름 삽입
    for (const string &region : regions)
    {
        trie.insert(region);
    }

    // 2. 각 지역 이름의 최소한의 고유한 길이 찾기
    int maxCodeLength = 1;
    for (const string &region : regions)
    {
        int minLength = trie.findMinUniqueLength(region);
        maxCodeLength = max(maxCodeLength, minLength);
        regionToCode[region] = region.substr(0, minLength); // 초기 코드 설정
    }

    // 3. 모든 코드가 동일한 길이를 가지도록 패딩(_ 추가)
    for (const string &region : regions)
    {
        string code = regionToCode[region];
        while (code.size() < maxCodeLength)
        {
            code += "_";
        }
        codes.push_back(code);
    }

    return codes;
}

int main()
{
    vector<string> regions = {"NETHERLAND", "NET", "NE", "MEXICO", "NORWAY", "NIGERIA"};
    //{"ABC", "BERLIN", "DUTCH", "DAEGU", "CHEZH"};
    vector<string> codes = generateRegionCodes(regions);

    cout << "지역 코드: ";
    for (const string &code : codes)
    {
        cout << code << " ";
    }
    cout << endl;

    return 0;
}
