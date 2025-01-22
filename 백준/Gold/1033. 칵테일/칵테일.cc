#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> num(10,1);
vector<int> con[10];

void dfs(vector<bool> &vis,int cur, int mul){
    for(int i=0;i<con[cur].size();i++){
        int node=con[cur][i];
        if(!vis[node]){
            num[node]*=mul;
            vis[node]=1;
            dfs(vis,node,mul);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;
    for(int i=1;i<n;i++){
        vector<bool> vis(10,0);
        int a,b,p,q;
        cin >> a >> b >> p >> q;
        int mula=num[b]/gcd(num[a],num[b])*p/gcd(p,q);
        int mulb=num[a]/gcd(num[a],num[b])*q/gcd(p,q);
        int imgcd=gcd(mula,mulb);
        mula/=imgcd;
        mulb/=imgcd;
        vis[a]=1; vis[b]=1;
        dfs(vis,a,mula);
        dfs(vis,b,mulb);
        num[a]*=mula;
        num[b]*=mulb;
        con[a].push_back(b);
        con[b].push_back(a);
    }
    for(int i=0;i<n;i++) cout << num[i] << ' ';
    return 0;
}