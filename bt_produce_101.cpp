#include <iostream>
#include <vector>

using namespace std;

int n;
int arr[11] = {0,};
char reserve[10];
int result;

void func(int now){
   //기저사례
    if (now == n-1){
        // 판별
        if (result == 0) return;
        if (result % 101 == 0){
            for (int i = 0; i < n; i++){
                cout << arr[i] << reserve[i];
            }
        }
        
        return;
    }


        // 처리
        int tmp = result;

        // 가라
        result *= arr[now+1]; //값 변
        reserve[now] = '*';
        func(now + 1); //재귀 시작
        result = tmp; // 값 복구
        
        
        result += arr[now+1];
        reserve[now] = '+';
        func(now + 1);
        result = tmp; // 값 복구
       
        result -= arr[now+1];
        reserve[now] = '-';
        func(now + 1);
        result = tmp; // 값 복구
}

int main() {
    cin >> n;
    reserve[n-1] = '\n';
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    result = arr[0];
    func(0);

}

// result = 22


// func : 첫 연산자를 +로 하거나 -로 하거나 *로 하거나

// +로 하는 경우:
// opArr[0] = '+';
// result += 79
// // 여기서부터 재귀 시작 (일단 무시)


// ---- result = 101 ----- 
// result -= 79;

// -로 하는 경우
// result -= 79;
// opArr[0] = '-';
// //다시 재귀 

// result += 79;

// result *= 79
// 재귀
// 복ㄱ 




// numArr[10] = {22, 79, 21};

// opArr[9] ={"+","-","-"};


