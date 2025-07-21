// 2025.07.01

/**
 * hash("abc") = (1 * 31^0) + (2 * 31^1) + (3 * 31^2)
 * pow is saving r^i value
 */

#include <iostream>
#include <string>
using namespace std;

const int r = 31, M = 1234567891;

int main() {
    int L;
    string str;
    cin >> L;
    cin >> str;

    long long result = 0;
    long long pow = 1;
    for (int i = 0; i < L; ++i) {
        int cur = str[i] - 'a' + 1;
        result = (result + cur * pow) % M;
        pow = (pow * r) % M;
    }

    cout << result;

    return 0;
}