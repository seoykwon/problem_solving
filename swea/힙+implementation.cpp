#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Heap {
private:
    vector<int> arr;
    int cnt;

    int getParent(int child) {
        return child / 2;
    }

    int getLeft(int parent) {
        return parent * 2;
    }

    int getRight(int parent) {
        return parent * 2 + 1;
    }

    void heapify() {
        int now = 1;
        while (getRight(now) <= cnt) {
            int larger = now;
            int left = getLeft(now);
            int right = getRight(now);
            if (arr[left] > arr[larger]) {
                larger = left;
            }
            if (arr[right] > arr[larger]) {
                larger = right;
            }
            if (larger != now) {
                swap(arr[now], arr[larger]);
                now = larger;
            } else {
                break;
            }
        }
    }

public:
    Heap() {
        arr.resize(100001);
        cnt = 0;
    }

    void add(int data) {
        arr[++cnt] = data;
        int now = cnt;
        while (now > 1) {
            int parent = getParent(now);
            if (arr[now] > arr[parent]) {
                swap(arr[now], arr[parent]);
                now = parent;
            } else {
                break;
            }
        }
    }

    int poll() {
        int max = arr[1];
        arr[1] = arr[cnt];
        arr[cnt] = 0;
        cnt--;
        heapify();
        return max;
    }

    bool isEmpty() {
        return cnt == 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        Heap heap;
        cout << "#" << tc << " ";

        for (int i = 0; i < N; i++) {
            int q, s;
            cin >> q;
            if (q == 1) {
                cin >> s;
                heap.add(s);
            } else {
                if (heap.isEmpty()) {
                    cout << -1 << " ";
                } else {
                    cout << heap.poll() << " ";
                }
            }
        }

        cout << "\n";
    }

    return 0;
}
