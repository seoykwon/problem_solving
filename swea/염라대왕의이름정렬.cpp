#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(string s1, string s2) {
    if (s1.length() != s2.length()) {
        return s1.length() > s2.length();
    }

    for (int i = 0; i < max(s1.length(), s2.length()); i++) {
        char c1 = i < s1.length() ? s1[i] : 0;
        char c2 = i < s2.length() ? s2[i] : 0;
        if (c1 != c2) {
            return c1 > c2;
        }
    }
    return true;
}

void merge(vector<string>& arr, int start, int center, int end){
    vector<string> head(arr.begin() + start, arr.begin() + center);
    vector<string> tail(arr.begin() + center, arr.begin() + end);

    int headPtr = 0;
    int tailPtr = 0;
    int index = start;

    while (index < end) {
        if (headPtr == head.size()) {
            arr[index] = tail[tailPtr];
            tailPtr++;
        }
        else if (tailPtr == tail.size()) {
            arr[index] = head[headPtr];
            headPtr;
        }
        else {
            if (compare(head[headPtr], tail[tailPtr])) {
                arr[index] = tail[tailPtr];
                tailPtr++;
            }
            else {
                arr[index] = head[headPtr];
                headPtr++;
            }
        }
        index++;
    }
}

void mergeSort(vector<string>& arr, int start, int end){
    if (end - start <= 1){
        return;
    }

    int center = start + (end - start) / 2;
    mergeSort(arr, start, center);
    mergeSort(arr, center, end);
    merge(arr, start, center, end);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++){
        int len;
        cin >> len;

        vector<string> words(len);
        for (int i = 0; i < len; i++){
            cin >> words[i];
        }

        mergeSort(words, 0, len);

        cout << "#" << tc << '\n';
        string prev = "";
        for (string word : words) {
            if (word != prev) {
                cout << word << "\n";
            }
            prev = word;
        }
    }

    return 0;
}