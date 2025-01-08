#include <iostream>

using namespace std;
typedef long long ll;

int isSqr[1000021];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    ll min, max;
    cin >> min >> max;

    ll cnt = (max - min) + 1;

    for (ll i = 2; i * i <= max; i++){
        ll ret = min / (i * i); // quotient

        // when quotient is smaller than min
        if (min % (i * i) != 0) ret++;

        while (ret * (i * i) <= max){
            if (isSqr[ret * (i * i) - min] == false) {
                isSqr[ret * (i * i) - min] = true;
                cnt--;
            }
            ret++;
        }
    }
    cout << cnt;

    return 0;
}