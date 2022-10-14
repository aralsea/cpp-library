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
#define INF 1000000007
using namespace std;
using pii=pair<int,int>;
using LL=int64_t;



int par[100005];//iの一つ上にあるやつ
int r[100005];//iの属する塊，グループの"高さ"（計算を速くするため）
void init(int n){
    for(int i=0;i<n;i++){
        par[i]=i;
        r[i]=0;
    }
}//全部バラバラの状態

int find(int x){
    if(par[x]==x){
        return x;
    }else{
        return par[x]=find(par[x]);
    }
}//一番上の付け根を求める

void unite(int x,int y){
    x=find(x);
    y=find(y);
    if(x==y) return;
    
    if(r[x]<r[y]){
        par[x]=y;
    }else{
        par[y]=x;
        if(r[x]==r[y]) r[x]++;
    }
}//xとyのグループを付け根でくっつける

bool same(int x,int y){
    return find(x)==find(y);
}//同じグループにいるかどうか
