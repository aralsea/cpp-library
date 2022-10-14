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
using pii=pair<int,int>;

int euclidean(int a, int b, int &x, int&y){/*a*x+b*y=1なるx,yを求める，aとbは互いに素*/
    if(b==1){
        x=0;
        y=1;
        return 0;
    }else{
        euclidean(b,a%b,y,x);
        y-=a/b*x;
        return 0;
    }

}

int inverse(int mod,int a){/*互除法をする,modとaは互いに素*/
    a=(a%mod+mod)%mod;
    int x,y;
    euclidean(a,mod,x,y);
    return x;
}

int main(){
    int a,b;
    cin>>a>>b;
    int x,y;
    euclidean(a,b,x,y);
    cout<<a<<"*"<<x<<"+"<<b<<"*"<<y<<"="<<(a*x+b*y)<<endl;

    return 0;
}