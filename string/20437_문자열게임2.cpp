// 2025.06.30
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;

    vector<int> alphabet[26];

    for (int tc = 1; tc <= T; tc++){
        string W;
        int K;
        cin >> W >> K;

        int mini = 100000;
        int maxi = 0;

        for (int i = 0; i < 26; i++) alphabet[i].clear();

        for (int i = 0; i < W.length(); i++){
            int num = W[i] - 'a';
            alphabet[num].push_back(i); // adding index of the alphabet
        }

        for (int i = 0; i < 26; i++){
            int vsize = (int)alphabet[i].size();
            // if the alphabet fulfills the requirement, check
            if (vsize >= K){
                for (int j = 0; j <= vsize - K; j++){
                    mini = min(mini, alphabet[i][j + K - 1] - alphabet[i][j] + 1);
                    maxi = max(maxi, alphabet[i][j + K - 1] - alphabet[i][j] + 1);
                }
            }
        }

        if (mini == 100000 || maxi == 0) cout << -1 << '\n';
        else cout << mini << " " << maxi << '\n';
    }
    return 0;
}