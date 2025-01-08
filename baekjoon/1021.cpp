#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    vector<int> v(n + 1);
    for (int i = 0; i < n; i++){
        cin >> v[i];
    }
}