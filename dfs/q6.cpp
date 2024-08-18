#include <iostream>
#include <string>
#include <vector>

using namespace std;

int ans = 0;
string target;
string bridge[2];
string path;
int cnt = 0;

void func(int idx, int bnum){
    if (path == target) {
        ans++;
        return;
    }

    if (bnum == 0) bnum = 1;
    else bnum = 0;

    for (int i = idx + 1; i < bridge[0].length(); i++){
        if (bridge[bnum][i] != target[cnt]) continue;

        cnt++;
        string temp = path;
        path += bridge[bnum][i];

        func(i, bnum);

        path = temp;
        cnt--;
    }
}

int main() {
    cin >> target;
    for (int i = 0; i < 2; i++){
        cin >> bridge[i];
    }

    func(-1, 0);

    func(-1, 1);
    cout << ans;
}