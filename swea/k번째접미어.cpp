#include <iostream>
#include <map>
#include <string>

using namespace std;

class Trie
{
public:
    char alphabet;              // 이 정점으로 이동하는 알파벳
    bool isWordEnd;             // 이 정점에서 끝나는 문자열이 존재하는 지 표현
    int cnt;                    // 이 정점을 root로 하는 subtree에 포함된 문자열 개수
    map<char, Trie *> children; // 각 문자에 대해 이동하는 다른 정점을 기억하는 Map

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
    { // 해당 정점에서 끝나는 단어가 있다면
        K--;
        if (K == 0)
        { // 원하는 문자열에 도달했다면,
            string result = "";
            for (int i = 0; i < depth; i++)
            {
                result += results[i];
            }
            cout << "#" << test_case << " " << result << endl;
            return;
        }
    }

    for (char i = 'a'; i <= 'z'; i++)
    { // 낮은 알파벳부터 하나씩 이동한다.
        if (trie->children.find(i) != trie->children.end())
        { // 해당 알파벳으로 이동할 수 있다면,
            Trie *child = trie->children[i];
            if (child->cnt < K)
            {                    // 해당 정점으로 이동하더라도 K 개의 문자열보다 적은 개수의 문자열이 있다면,
                K -= child->cnt; // 빠르게 해당 개수만큼 skip 한다.
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
    cout << "#" << test_case << " " << str << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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
        { // i 번째 문자에서 시작하는 접미열을 Trie에 반영
            Trie *indexTrie = head;

            for (int j = i; j < len; j++)
            { // j 번째 문자로 이동하기
                char alphabet = words[j];

                if (indexTrie->children.find(alphabet) == indexTrie->children.end())
                { // 새로운 문자라면 정점 추가하기
                    Trie *newTrie = new Trie(alphabet);
                    indexTrie->children[alphabet] = newTrie;
                }
                indexTrie = indexTrie->children[alphabet];
                indexTrie->cnt++; // 하위 문자열 개수 증가
            }

            indexTrie->isWordEnd = true;
        }
        results[len] = '\0';
        dfs(head, 0, test_case);
        delete head;
    }

    return 0;
}
