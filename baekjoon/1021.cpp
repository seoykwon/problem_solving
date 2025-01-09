/**
 * 양쪽에서 입력과 삭제가 되는 자료구조를 써야 함 -> deque 사용
 */

#include <iostream>
#include <deque>
using namespace std;

deque <int> dq;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    int r, l, cnt = 0, tmp;

    for (int i = 1; i <= n; i++){
        dq.push_back(i);
    }

    while(m--){
        cin >> tmp;

        for (int i = 0; i < dq.size(); i++){
            // tmp 위치 찾고, 왼쪽과 오른쪽의 길이 구하기기
            if (dq[i] == tmp){
                r = i;
                l = dq.size() - r;
                break;
            }
        }

        if (r <= l){
            while(1){
                if (dq.front() == tmp){
                    dq.pop_front();
                    break;
                }
                dq.push_back(dq.front());
                dq.pop_front();
                cnt++;
            }
        } // 오른쪽으로 회전

        else if (r > l){
            while(1){
                if (dq.front() == tmp){
                    dq.pop_front();
                    break;
                }
                dq.push_front(dq.back());
                dq.pop_back();
                cnt++;
            } // 왼쪽이 오른쪽보다 작다면 왼쪽으로 회전
        }
    }
    cout << cnt;
    return 0;
}