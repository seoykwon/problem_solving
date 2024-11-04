#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct node
{
    string word;
    int cnt;
};

int main()
{
    // freopen("input.txt", "r", stdin);

    string lyrics;
    // cin >> lyrics;
    getline(cin, lyrics);

    int n;
    cin >> n;

    // unordered_map<string, int> search;
    vector<node> search;

    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;

        // search.insert({tmp, 0});
        search.push_back({tmp, 0});
    }

    // for (&auto key : search)
    for (auto &key : search)
    {
        // The error occurs because unordered_map elements are accessed by keys, not by indices.
        // In your code, search[i] tries to access the i-th element by index, which is not valid for unordered_map.
        // size_t pos = lyrics.find(search[i].first);
        size_t pos = lyrics.find(key.word);

        while (pos != string::npos)
        {
            key.cnt++;
            pos = lyrics.find(key.word, pos + 1);
        }
    }

    for (auto &e : search)
    {
        cout << e.cnt << endl;
    }

    return 0;
}