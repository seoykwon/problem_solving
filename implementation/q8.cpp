#include <iostream>

using namespace std;

int N;
char d;
int s;
int canvas[6][6];

void color(){
    if (d == 'R'){
        int yd = 1;
        int xd = 1;
        
    }
    else if (d == 'L'){

    }
}

int main(){

    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            canvas[i][j] = 0;
        }
    }
    cin >> N;

    for (int i = 1; i < N; i++){
        cin >> s >> d;

        color();
    }
}