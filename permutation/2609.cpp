#include <iostream>

using namespace std;

int gcdBad(int a, int b){
    // 두 수 중 더 작은 거 기준으로 하나씩 감소하며 공약수 있는지 판단
    for (int i = min(a, b); i > 1; i--){
        // 공약수 존재하면 바로 리턴 -> 최대공약수
        if (a % 1 == 0 && b % i == 0){
            return i;
        }
    }
    return 1; // 끝까지 없다면 최대공약수 1
}

int gcdRecursion(int a, int b){
    if (b == 0) return a; // b가 0이면 a가 최대공약수   

    // a%b 구한 후 b와 자리 바꾸어서 호출
    return gcdRecursion(b, a % b);
}

int main(){
    int a, b;
    cin >> a >> b;

    // int g = gcdBad(a, b);
    int g = gcdRecursion(max(a, b), min(a, b));
    int l = (a * b) / g;

    cout << g << endl << l << endl;

    return 0;
}