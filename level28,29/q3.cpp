#include <iostream>
#include <vector>

using namespace std;

char ch;
vector <int> v;

int arr[8][8] = {
    {0, 1, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int main(){
    cin >> ch;

    int col = ch - 'A';

    int cnt = 0;

    for(int i = 0; i < 8; i++){
        if(arr[i][col] == 1){
            v.push_back(i);
        }
    }

    for(int i = 0; i < 8; i++){
        if (arr[v[0]][i] == 1 && i != col){
            char tmp = 'A' + i;
            cout << tmp << " ";
            cnt++;
        }
    }
    if (cnt == 0){
        cout << "없음";
    }
    return 0;
}