#include <iostream>

using namespace std;

int arr[5][5] = {
    {0, 1, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0}
};

int popular = 0;
int maxV = 0;

int main(){
    for(int i = 0; i < 5; i++){
        int cnt = 0;
        for(int j = 0; j < 5; j++){
            if (arr[i][j] == 1){
                cnt++;
            }
            if (cnt > maxV){
                maxV = cnt;
                popular = i;
            }
        }
    }

    if(popular == 0) cout << "Amy";
    else if (popular == 1) cout << "Bob";
    else if (popular == 2) cout << "Chloe";
    else if (popular == 3) cout << "Diane";
    else if (popular == 4) cout << "Edger";

    return 0;
}