#include <iostream>
#include <map>
#include <string>

using namespace std;

class Trie
{
public:
    char alphabet;
    bool isWordEnd;
    int cnt;
    map<char, Trie *> children;

    Trie(char alphabet) : alphabet(alphabet), isWordEnd(false), cnt(0) {}

    Trie() : alphabet('\0'), isWordEnd(false), cnt(0) {}
};

int K;
char results[401];

void dfs(Trie *trie, int depth, int tc)
{
    if (K == 0)
        return;

    if (trie->isWordEnd)
    {
        K--;
        if (K == 0)
        {
            if (trie->cnt < K)
            {
                string result = "";
                for (int i = 0; i < depth; i++)
                {
                    result += results[i];
                }
                cout << "#" << tc << " " << result << endl;
                return;
            }
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        cin >> K;
        string word;
        cin >> word;

        int len = word.length();

        Trie *head = new Trie();

        for (int i = 0; i < len; i++)
        {
            Trie *idx = head;

            for (int j = 0; j < len; j++)
            {
                char alphabet = word[j];

                if (idx->children.find(alphabet) == idx->children.end())
                {
                    Trie *newTrie = new Trie(alphabet);
                    idx->children[alphabet] = newTrie;
                }
                idx = idx->children[alphabet];
                idx->cnt++;
            }
            idx->isWordEnd = true;
        }
        results[len] = '\0';
        dfs(head, 0, tc);
        delete head;
    }
}