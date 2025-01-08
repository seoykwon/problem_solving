#include <iostream>
using namespace std;

int T, x, y;

void Solve(){
    long long cmp{y-x}, n{1};
    while(n*n<cmp) {
       n++;
    }
    long long tmp = 2 * n - 1;
    if(cmp<=(n*n+(n-1)*(n-1)-1)/2) {
       cout<<tmp-1<<'\n';
    } else {
       cout<<tmp<<'\n';
    }
}

void Init(){
    cin>>x>>y;
}

int main(){
    cin.tie(nullptr)->ios_base::sync_with_stdio(false);
    cin>>T;
    while(T--){
        Init();
        Solve();
    }
    return 0;
}