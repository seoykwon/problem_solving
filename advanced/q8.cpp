#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

vector<long long> balloon;
int used_order[12] = {0,};
// we will be using usedorder array from index 1, indicating order 1 and reaching to N

// struct possibility {
//     int potentialScore;
//     int order;
//     int index;

//     // I want to implement max heap
//     bool operator<(possibility b){
//         if (potentialScore < b.potentialScore) return true;
//         if (potentialScore > b.potentialScore) return false;
//         return false;
//     }
// };
struct possibility {
    long long potentialScore;
    int order;
    int index;
};

// max heap
struct cmp{
    // I want to implement max heap
    bool operator()(possibility a, possibility b){
        if (a.potentialScore < b.potentialScore) return true;
        if (a.potentialScore > b.potentialScore) return false;
        return false;
    }
};

int bfs(int N){
    // priority_queue<possibility> pq;
    priority_queue<possibility, vector<possibility>, cmp> pq;

    for (int i = 0; i < N; i++){
        if (i == 0){
            pq.push({balloon[1], 1, i});
            continue;
        }
        else if (i == N - 1){
            pq.push({balloon[N - 2], 1, i});
            continue;
        }

        long long mul = balloon[i - 1] * balloon[i + 1];
        pq.push({mul, 1, i});
    }

    while(!pq.empty()){
        possibility now = pq.top();
        pq.pop();

        if (used_order[now.order] == 1) continue;

        // by popping out from the pq, the balloon is finally actually popped
        used_order[now.order] = 1;

        // reached the end
        if (now.order == N) return now.potentialScore;

        // erase popped balloon from balloon vector
        balloon.erase(balloon.begin() + now.index);

        int sz = balloon.size();

        if (sz == 1){
            pq.push({now.potentialScore + balloon[0], now.order + 1, 0});
            continue;
        }

        for (int i = 0; i < sz; i++){
            if (i == 0){
                pq.push({now.potentialScore + balloon[1], now.order + 1, i});
                continue;
            }
            if (i == sz - 1){
                pq.push({now.potentialScore + balloon[sz - 2], now.order + 1, i});
                continue;
            }

            long long mul = balloon[i - 1] * balloon[i + 1];
            pq.push({now.potentialScore + mul, now.order + 1, i});
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++){
        balloon.clear();
        memset(used_order, 0, sizeof(used_order));

        int N;
        cin >> N;

        for (int b = 0; b < N; b++){
            long long tmp;
            cin >> tmp;
            balloon.push_back(tmp);
        }

        // when there is only one balloon 
        if (N == 1){
            cout << "#" << tc << " " << balloon[0] << '\n';
            continue;
        }

        int score = bfs(N);

        cout << "#" << tc << " " << score << '\n';
    }
}

/**
 * Debugging
 * 1. 초기화 해주기. 여러 테스트 케이스에게 비어 있는 풍선 벡터와 사용된 풍선 배열을 건네줘야 한다.
 * 2. 제일 어려운 부분. 풍선이 계속 터지면서 벡터 사이즈는 줄어든다.
 * 동시에 인덱스 또한 바뀌기 때문에 인덱스로 사용된 풍선이라고 마킹할 수가 없다.
 * 심지어 풍선마다 고유한 숫자 값을 갖는 것도 아니다. 어떻게 마킹해야 할까?
 * 
 * 
 * 오케이.
 * 위에 코드는 틀린 접근 방법이다.
 * DP로 풀어야 함
 */