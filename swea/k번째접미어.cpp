#include <iostream>
#include <map>
#include <string>

using namespace std;

class Trie
{
public:
    // 이 정점으로 이동하는 알파벳
    char alphabet;
    // 이 정점에서 끝나는 문자열이 존재하는 지 표현
    bool isWordEnd;
    // 이 정점을 root로 하는 subtree에 포함된 문자열 개수
    int cnt;
    // 각 문자에 대해 이동하는 다른 정점을 기억하는 map
    map<char, Trie *> children;

    Trie(char alphabet) : alphabet(alphabet), isWordEnd(false), cnt(0) {}

    Trie() : alphabet('\0'), isWordEnd(false), cnt(0) {}
};

int K;
char results[101];

void dfs(Trie *trie, int depth, int test_case)
{
    if (K == 0)
        return;

    if (trie->isWordEnd)
    {
        K--;
        if (K == 0)
        {
            string result = "";
            for (int i = 0; i < depth; i++)
            {
                result += results[i];
            }
            cout << "#" << test_case << " " << result << "\n";
            return;
        }
    }

    for (char i = 'a'; i <= 'z'; i++)
    {
        if (trie->children.find(i) != trie->children.end())
        {
            Trie *child = trie->children[i];
            if (child->cnt < K)
            {
                K -= child->cnt;
                continue;
            }

            results[depth] = i;
            dfs(trie->children[i], depth + 1, test_case);
            results[depth] = '\0';
        }
    }
}

void print(const string &str, int test_case)
{
    cout << "#" << test_case << " " << str << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++)
    {
        Trie *head = new Trie();
        cin >> K;
        string words;
        cin >> words;
        int len = words.length();

        if (K > len)
        {
            print("none", test_case);
            continue;
        }

        for (int i = 0; i < len; i++)
        {
            Trie *indexTrie = head;

            for (int j = 0; j < len; j++)
            {
                char alphabet = words[j];

                if (indexTrie->children.find(alphabet) == indexTrie->children.end())
                {
                    Trie *newTrie = new Trie(alphabet);
                    indexTrie->children[alphabet] = newTrie;
                }
                indexTrie = indexTrie->children[alphabet];
                indexTrie->cnt++;
            }
            indexTrie->isWordEnd = true;
        }
        results[len] = '\0';
        dfs(head, 0, test_case);
        delete head;
    }
    return 0;
}