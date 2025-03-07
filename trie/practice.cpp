/**
 * 선행 스킬이란 어떤 스킬을 배우기 전에 먼저 배워야 하는 스킬을 뜻합니다. 예를 들어 선행 스킬 순서가 스파크 -> 라이트닝 볼트 -> 썬더 일 때, 썬더를 배우려면 먼저 라이트닝 볼트를 배워야 하고, 라이트닝 볼트를 배우려면 먼저 스파크를 배워야 합니다.
위 순서에 없는 다른 스킬 (힐링 등)은 순서에 상관없이 배울 수 있습니다. 따라서 스파크 -> 힐링 -> 라이트닝 볼트 -> 썬더 와 같은 스킬트리는 가능하지만, 썬더 -> 스파크 나 라이트닝 볼트 -> 스파크 -> 힐링 -> 썬더 와 같은 스킬트리는 불가능합니다.
선행 스킬 순서 skill 과 유저들이 만든 스킬트리를 담은 배열 skill_trees가 매개변수로 주어질 때, 가능한 스킬트리 개수를 return하는 solution 함수를 작성해주세요.

제한조건:
스킬은 알파벳 대문자로 표기하며, 모든 문자열은 알파벳 대문자로만 이루어져 있습니다.
스킬 순서와 스킬트리는 문자열로 표기합니다. 예를 들어, C -> B -> D 라면 CBD로 표기합니다.
선행 스킬 순서 skill의 길이는 1 이상 26 이하이며, 스킬은 중복해 주어지지 않습니다.
skill_trees는 길이 1 이상 20 이하인 배열입니다.
skill_trees의 원소는 길이가 2이상 26 이하인 문자열이며, 스킬이 중복해 주어지지 않습니다.

입출력 예
skill "CBD"
skill_trees ["BACDE", "CBADF", "AECB", "BDA"]
return 2

입출력 예 설명
"BACDE": B 스킬을 배우기 전에 C 스킬을 먼저 배워야 함. 불가능한 스킬트리
"CBADF": 가능
"AECB": 가능
"BDA": B 스킬을 배우기 전에 C 스킬 먼저 배워야 함. 불가능
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int solution(string skill, vector<string> skill_trees)
{
    int count = 0;

    for (const string &tree : skill_trees)
    {
        string filtered = "";

        // skill 순서에 포함된 문자만 추출
        for (char ch : tree)
        {
            if (skill.find(ch) != string::npos)
            {
                filtered += ch;
            }
        }

        // 필터링된 문자열이 skill의 접두사인지 확인
        if (skill.substr(0, filtered.size()) == filtered)
        {
            count++;
        }
    }

    return count;
}

int main()
{
    string skill = "CBD";
    vector<string> skill_trees = {"BACDE", "CBADF", "AECB", "BDA"};
    cout << solution(skill, skill_trees) << endl; // 출력: 2
    return 0;
}

// ###############################################
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Trie Node structure
struct TrieNode
{
    unordered_map<char, TrieNode *> children;
    bool isEnd = false;
};

// Trie class for skill sequence validation
class Trie
{
public:
    TrieNode *root;
    Trie(string skill)
    {
        root = new TrieNode();
        buildTrie(skill);
    }

    void buildTrie(string skill)
    {
        TrieNode *node = root;
        for (char ch : skill)
        {
            if (node->children.find(ch) == node->children.end())
            {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool isValidSkillTree(string skillTree)
    {
        TrieNode *node = root;
        unordered_map<char, bool> learned;

        for (char ch : skillTree)
        {
            if (node->children.find(ch) != node->children.end())
            {
                if (node != root && !node->isEnd)
                    return false;
                node = node->children[ch];
                learned[ch] = true;
            }
            else if (learned.find(ch) == learned.end())
            {
                continue;
            }
        }
        return true;
    }
};

int solution(string skill, vector<string> skill_trees)
{
    Trie trie(skill);
    int count = 0;

    for (const string &tree : skill_trees)
    {
        if (trie.isValidSkillTree(tree))
        {
            count++;
        }
    }
    return count;
}

int main()
{
    string skill = "CBD";
    vector<string> skill_trees = {"BACDE", "CBADF", "AECB", "BDA"};
    cout << solution(skill, skill_trees) << endl; // Output: 2
    return 0;
}
