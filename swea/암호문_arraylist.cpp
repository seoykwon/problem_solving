#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    cin.ignore();

    string s;
    getline(cin, s);
    stringstream st(s);
}