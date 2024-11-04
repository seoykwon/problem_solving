#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    vector<int> sq(N);
    unordered_map<int, int> mp;

    for (int i = 0; i < N; i++)
    {
        cin >> sq[i];
        mp[sq[i]]++;
    }

    vector<int> queries(M);
    for (int i = 0; i < M; i++)
    {
        cin >> queries[i];
    }

    for (int i = 0; i < M; i++)
    {
        cout << mp[queries[i]] << " ";
    }
}