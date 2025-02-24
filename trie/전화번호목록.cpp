#include <bits/stdc++.h>
using namespace std;

/**
 * char *str points to the first character of the string.
 * str + 1 shifts the pointer to the next character.
 * By recursively calling the function with str + 1, we naturally move through each character in the string without explicitly tracking the index.
 * */

struct Trie
{
    map<char, Trie *> node;
    bool finish;

    Trie()
    {
        finish = false;
    }

    void insert(const char *str)
    {
        if (*str == '\0')
        {
            finish = true;
            return;
        }

        if (node.find(*str) == node.end())
            node[*str] = new Trie();

        node[*str]->insert(str + 1);
    }

    bool find(const char *str)
    {
        if (*str == '\0')
        {
            return false;
        }

        if (finish == true)
        {
            return true;
        }

        if (node.find(*str) == node.end())
            return false;

        return node[*str]->find(str + 1);
    }
};

char input[100000][11];

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        Trie *root = new Trie();

        for (int i = 0; i < n; i++)
        {
            cin >> input[i];
            root->insert(input[i]);
        }

        for (int i = 0; i < n; i++)
        {
            if (root->find(input[i]))
            {
                cout << "NO" << '\n';
                break;
            }
            else if (i == n - 1)
            {
                cout << "YES" << '\n';
            }
        }

        delete root;
    }
}
