#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> signals){
    int n = signals.size();
    vector<long long> a(n), b(n), L(n);
    long long lcm = 1;
    for (int i = 0; i < n; ++i){
        a[i] = signals[i][0];
        b[i] = signals[i][1];
        L[i] = (long long)signals[i][0] + signals[i][1] + signals[i][2];
        lcm = lcm / __gcd(lcm, L[i]) * L[i];
    }

    auto isGreen = [&](int i, long long t) {
        long long r = t % L[i];
        return r >= a[i] && r < a[i] + b[i];
    };
    auto nextGreen = [&](int i, long long t) -> long long {
        long long r = t % L[i];
        if (r >= a[i] && r < a[i] + b[i]) return t;
        if (r < a[i]) return t + (a[i] - r);
        return t + (L[i] - r) + a[i];
    };

    long long t = 0;
    while (t < lcm) {
        long long next_t = t;
        bool all = true;
        for (int i = 0; i < n; ++i){
            if (!isGreen(i, t)) {
                all = false;
                next_t = max(next_t, nextGreen(i, t));
            }
        }
        if (all) return (int)(t + 1);
        t = next_t;
    }
    return -1;
}