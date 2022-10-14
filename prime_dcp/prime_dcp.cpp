#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <functional>
#include <set>
#include <map>
#include <tuple>
#include <bitset>
#include <random>

#define REP(i,n) for(int i=0;i<n;i++)
#define INF 100000000000007
using namespace std;
using ll = long long;
using pii=pair<int,int>;
using pll = pair<ll, ll>;

vector<pll> fs;//素因数分解の素数，指数のペア
//最悪計算量はO((base)^1/2)
void factorization(ll base){//baseを素因数分解
    //base以下のiが約数か
    for(ll i=2;i*i<=base;i++){/*ここをintにすると遅い(19734861857639539とか46116646144580591とか)*/
        //iで割り切れるなら限界まで割る
        
        if(base%i==0){
            
            ll cnt=0;
            while(base%i==0){
                base/=i;
                cnt++;
            }
            fs.push_back(make_pair(i,cnt));
        }
    }
    //baseが素数
    if(base>1){
        fs.push_back(make_pair(base,1));
    }
}

int main(){
    ll n;
    cin>>n;
    factorization(n);
    
    
    for(auto p : fs){
        int64_t prime, index;
        tie(prime,index)=p;
        

        cout<<prime<<'^'<<index<<endl;
    }

    
}