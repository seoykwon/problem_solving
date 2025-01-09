/**
 * 수학적 공식을 이용해 풀 수 있는 문제
 * 
 * 길이가 L인 연속된 정수의 합이 N이라고 했을 때
 * x : 수열의 처음 시작
 * N = x + (x + 1) + (x + 2) + (x + 3) + ... + (x + (L - 1))
 * 이는 N = Lx + (1 + 2 + 3 + ... + (L - 1))
 * 
 * (1 + 2 + 3 + ... + (L - 1))를 t로 치환했을 때
 * Lx = N - t
 * x = (N - t) / L
 * 
 * 여기서 x는 정수이고, 0보다 크거나 같아야하므로
 * (N - t) % L == 0 과 (N - t) / L >= 0을 만족시켜야 한다.
 * 
 * 리스트의 길이가 L일 때 위의 조건들을 만족시키지 못한다면, 
 * 100보다 작거나 같을 때까지 L을 1씩 늘려가며 만족하는 L을 찾는다.
 * 만약 L이 100을 넘어간다면 -1을 출력한다.
 */

#include <iostream>
using namespace std;

int seq_sum(int n){
    // 1부터 n까지의 합 (t)
    return n * (n + 1) / 2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // freopen("input.txt", "r", stdin);
    int n, l;
    cin >> n >> l;

    for (int i = l; i <= 100; i++){ // 리스트 길이 <= 100
        if ((n - seq_sum(l - 1)) / l >= 0 && (n - seq_sum(l - 1)) % l == 0){
            // x가 0보다 크거나 같고, 정수일 때만

            int x = (n - seq_sum(l - 1)) / l;
            for (int j = x; j < (x + l); j++){
                // x부터 길이가 l만큼 출력
                cout << j << " ";
            }
            cout << '\n';
            return 0;
        }
        l++; // l의 길이일 때 충족되지 않으면 l + 1
    }

    cout << -1;
    return 0;
}