#include <iostream>

using namespace std;

int n;
int arr[10][10];

int main(){
    cin >> n;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }

    cout << "boss:";
    for(int i = 0; i < n; i++){
        if(arr[i][0] == 1) cout << i << " ";
    }
    cout << endl;

    cout << "under:";
    for(int j = 0; j < n; j++){
        if(arr[0][j] == 1) cout << j << " ";
    }
    cout << endl;
}