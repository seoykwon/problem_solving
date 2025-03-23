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

    Trie(char alphabet) :
};