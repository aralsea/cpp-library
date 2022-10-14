#include <bits/stdc++.h>
using namespace std;
#define INF 1000000007
#define REP(i,n) for(int i=0;i<n;i++)

using pii=pair<int,int>;

//binary indexed tree
//BIT Zは長さNの配列
//Z[i]+=x がO(log N)
//Z[0]+Z[1]+...+Z[k]がO(log N)
//cf. 普通の配列だとそれぞれO(1),O(N)
//cf. 累積和だとそれぞれO(N),O(1)
class BIT {
public:
    int size_ = 1;
    vector<int> bit;

    void init(int sz){
        size_ = sz + 1;
        bit.resize(size_, 0);
    }

    void add(int position, long long x){
        position++;//1-indexed
        while(position<=size_){
            bit[position]+=x;
            position += (position & (-position));
        }
    }

    long long sum(int position){
        position++;
        long long s = 0;
        while(position>0){
            s += bit[position];
            position -= (position & (-position));
        }
        return s;
    }


};


int main() {
    int N=1000;
    BIT Z;
    Z.init(N+5);
    Z.add(1, 15);//Z[1]+=15;
    cout<<Z.sum(10)<<endl;//Z[0]+...+Z[10]
    cout<<Z.sum(0)<<endl;//Z[0]

    return 0;
}