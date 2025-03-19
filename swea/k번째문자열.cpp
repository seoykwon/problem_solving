#include <iostream>
#include <map>
#include <string>

using namespace std;

class Trie
{
public:
    char alphabet;
    bool isWordEnd;
    int cnt = 0;
    map<char, Trie *> children;

    Trie(char alphabet) : alphabet(alphabet), isWordEnd(false), cnt(0) {}

    Trie() : alphabet('\0'), isWordEnd(false) {}
};

int K;
char results[405];

int insert(const string &words, int idx, Trie *trie)
{
    if (idx == words.length())
    {
        return 0;
    }

    char alphabet = words[idx];

    int subCnt = 0;
    if (trie->children.find(alphabet) == trie->children.end())
    {
        Trie *newTrie = new Trie(alphabet);
        newTrie->cnt = 1;
        subCnt = 1;
        trie->children[alphabet] = newTrie;
    }

    subCnt += insert(words, idx + 1, trie->children[alphabet]);
    trie->cnt += subCnt;

    return subCnt;
}

void dfs(Trie *trie, int depth, int test_case)
{
    if (K == 0)
        return;

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

void result(const string &str, int test_case)
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
        K++;
        string words;
        cin >> words;
        int len = words.length();
        for (int i = 0; i < len; i++)
        {
            insert(words, i, head);
        }
        results[len] = '\0';
        dfs(head, 0, test_case);
        if (K > 0)
        {
            result("none", test_case);
        }
    }
    return 0;
}