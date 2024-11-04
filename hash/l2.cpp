#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    // unordered_map<string, int> v = {
    //     {'POP', 0}, {'TOM', 0}, {'MC', 0}, {'JASON', 0}, {'KFC', 0}};
    unordered_map<string, int> v = {
        {"POP", 0}, {"TOM", 0}, {"MC", 0}, {"JASON", 0}, {"KFC", 0}};

    string tmp;

    for (int i = 0; i < n; i++)
    {
        cin >> tmp;

        if (v.find(tmp) != v.end())
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
}