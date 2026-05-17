# products 길이 <= 1000000
# 1 <= products[i] 상품 무게  <= 10000000
# 1 <= w <= 10000000

# 시간 제한 10초, 메모리 제한 20gb 인데, 내가 접근한 이 알고리즘 맞는거야?
# products = 상품의 무게
# w = 상품 나올 때 통로에 걸리는 무게 기준
# 버튼을 눌렀을 때 빠져나온 상품들 무게 합 중 최댓값

from collections import deque

def solve(products, w):
    q = deque(products)
    sessions = []
    clog = 0
    tmp = 0
    flag = 0

    while q:
        if clog == 0:
            clog = q.popleft()
            if clog >= w:
                sessions.append(clog)
                clog = 0
                continue
            else:
                flag = 1
                continue

        if flag:
            tmp += q.popleft()
            if tmp >= clog:
                sessions.append(tmp + clog)
                clog = 0
                tmp = 0
                flag = 0

    return max(sessions) if sessions else 0

#include <vector>
using namespace std;

long long solve(const vector<int>& products, int w){
    long long result = 0;
    long long stuck = 0;
    long long onTop = 0;

    for (int p : products) {
        if (stuck == 0) {
            if (p >= w) {
                if (p > result) result = p;
            } else {
                stuck = p;
            }
        }
        else {
            onTop += p;
            if (onTop >= stuck) {
                long long session = stuck + onTop;
                if (session > result) result = session;
                stuck = 0;
                onTop = 0;
            }
        }
    }
    return result;
}

public class Solution {
    public long solve(int[] products, int w) {
        long result = 0;
        long stuck = 0;
        long onTop = 0;

        for (int p : products) {
            if (stuck == 0) {
                if (p >= w) {
                    if (p > result) result = p;
                }
                else {
                    stuck = p;
                }
            }
            else {
                onTop += p;
                if (onTop >= stuck) {
                    long session = stuck + onTop;
                    if (session > result) result = session;
                    stuck = 0;
                    onTop = 0;
                }
            }
        }
        return result;
    }
}