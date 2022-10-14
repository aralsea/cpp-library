#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)

template <typename T>//テンプレート，RMQ<int>ってすると以下T = int
class RMQ{
    const T INF = std::numeric_limits<T>::max();
    //T型の最大値

    int n;//葉の数
    vector<T> binary_tree;//完全二分木を表す配列
    //binary_tree[i] = iに対応する半開区間における配列Aの最小値

    T query_sub(int a, int b, int k, int l, int r){
        //k：いま見てるノードのindex，[l,r)：そのノードの表す区間
        //[l,r) \cap [a, b)での最小値を返す関数

        if(r<=a || b<=l){//[a, b)と[l, r)が交わらないとき
            return INF;
        }else if(a<=l && r<=b){
            //[l, r)が[a, b)に含まれるとき，[l, r)での最小値を返す
            return binary_tree[k];
        }else{
            //包含はないが交わるとき，2人の子区間を調べる
            T candidate_l = query_sub(a, b, 2*k+1, l, (l + r)/2);
            T candidate_r = query_sub(a, b, 2*k+2, (l + r)/2, r);

            return min(candidate_l, candidate_r);
        }
    }

public:
    //コンストラクタ
    //n_ 個の数値の配列Aに対応するRMQを作る．n=（n_以上の最小の2べき）
    //binary_treeの大きさは2n-1を超えるようにn_ * 4で初期化
    RMQ(int n_) : n(), binary_tree(n_ * 4, INF){
        int x = 1;
        while(n_ > x){
            x *= 2;
        }
        n = x;
    }

    //A[i]の値をxに更新 O(log n)
    void update(int i, T x){
        i += n-1;//A[i]はbinary_tree[i+n-1]に入ってる
        binary_tree[i] = x;//更新
        while(i>0){
            i = (i-1)/2;
            //親を2人の子の最小値に更新
            binary_tree[i] = min(binary_tree[2*i + 1], binary_tree[2*i+2]);
        }
    }

    //区間[a,b)での最小値を取得 O(log n)
    T query(int a, int b){
        return query_sub(a, b, 0, 0, n);
    }

};

int main(){
    int n, q;
    cin>>n>>q;
    RMQ<int> Z(n);

    vector<int> ans;
    for(int i=0;i<q;i++){
        int com, x, y;
        cin>>com>>x>>y;
        if(com == 0){
            Z.update(x, y);
        }else{
            ans.push_back(Z.query(x, y+1));
        }
    }

    for(auto a : ans){
        cout<<a<<endl;
    }
    return 0;
}