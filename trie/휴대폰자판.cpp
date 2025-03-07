#include <bits/stdc++.h>
#include <unordered_map>
#include <iostream>

using namespace std;

struct Trie
{
    bool isEnd;
    unordered_map<char, Trie *> child;

    Trie() : isEnd(false) {} // Initialize isEnd in the constructor

    void Insert(string str)
    {
        Trie *now = this;
        for (int i = 0; i < str.length(); ++i)
        {
            if (now->child.find(str[i]) == now->child.end())
            {
                now->child[str[i]] = new Trie();
            }
            now = now->child[str[i]];
        }
        now->isEnd = true; // Mark the end of the word after the loop
    }

    int AutoComplete(string str)
    {
        int count = 1; // The first character is always typed
        Trie *now = this->child[str[0]];

        for (int i = 1; i < str.length(); ++i)
        {
            if (!now)
                return count; // Prevent null pointer dereference

            if (now->isEnd || now->child.size() > 1)
                count++;

            now = now->child[str[i]];
        }
        return count;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    while (cin >> n)
    {
        vector<string> words(n);
        for (int i = 0; i < n; ++i)
            cin >> words[i];

        Trie *root = new Trie();
        for (int i = 0; i < n; ++i)
            root->Insert(words[i]);

        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            sum += root->AutoComplete(words[i]);
        }

        double result = (double)sum / words.size();
        cout << fixed << setprecision(2) << result << '\n';

        delete root; // Clean up memory
    }
}
