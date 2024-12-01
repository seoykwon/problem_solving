#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<string, int> um;
int parent[100001];
string DAT[100001];

int Find(int now)
{
    if (now == parent[now])
        return now;
    return parent[now] = Find(parent[now]);
}

void Union(int A, int B)
{
    int pa = Find(A);
    int pb = Find(B);
    if (pa == pb)
        return;
    parent[pb] = pa;
}

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < N * 2; i++)
        parent[i] = i;

    int num = 0;

    for (int i = 0; i < N; i++)
    {
        string A, B;
        cin >> A >> B;
        if (um.find(A) == um.end())
        {
            um[A] = num;
            DAT[num] = A;
            num++;
        }
        if (um.find(B) == um.end())
        {
            um[B] = num;
            DAT[num] = B;
            num++;
        }
        if (Find(um[A]) == Find(um[B]))
            continue;
        Union(um[A], um[B]);
    }

    string target;
    cin >> target;
    vector<string> v;

    for (int i = 0; i < num; i++)
    {
        if (Find(i) == Find(um[target]))
            v.push_back(DAT[i]);
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << '\n';
    }
}