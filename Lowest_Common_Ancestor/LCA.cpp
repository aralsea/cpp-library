#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)

using Graph = vector<vector<int>>;


class LCA{
    int N;//木の頂点数
    Graph tree;
    int root;
    vector<bool> already_seen;
    vector<int> distance_from_root;
    vector<vector<int>> doubling_ancestor;
    //doubling_ancestor[k][i] = ノードiの2^k上の祖先

    void dfs(int v, int d){
        //v：いま見てるノード，d：今のrootからの距離
        already_seen[v] = true;
        distance_from_root[v] = d;
        for(auto next_v : tree[v]){
            if(!already_seen[next_v]){
                doubling_ancestor[0][next_v] = v;
                dfs(next_v, d + 1);
            }
        }
    }


    void init(){
        int K = 1;
        while((1<<K)<N) K++;//Kは2^(k-1)<N<=2^Kを満たす
        doubling_ancestor.assign(K, vector<int>(N, -1));
        dfs(0, 0);
        for(int k = 0;k+1<K;k++){
            for(int v = 0;v<N;v++){
                if(doubling_ancestor[k][v]>=0){
                    doubling_ancestor[k + 1][v]=doubling_ancestor[k][doubling_ancestor[k][v]];
                }
            }
        }
    }

public:
    LCA(const Graph &G, int rt = 0){
        tree = G;
        root = rt;
        N = tree.size();
        already_seen.assign(N, false);
        distance_from_root.resize(N);
        init();
    }

    int query(int a, int b){//aとbの最近共通祖先を求める
        
        if(distance_from_root[a]<distance_from_root[b]) swap(a, b);
        int K = doubling_ancestor.size();

        //aとbの高さを揃える
        for(int k = 0;k<K;k++){
            if((distance_from_root[a] - distance_from_root[b])>>k & 1){
                a = doubling_ancestor[k][a];
            }
        }

        if(a == b) return a;
        for(int k = K - 1;k>=0;k--){
            //aとbが異なるギリギリまで動かす（兄弟になるまで）
            if(doubling_ancestor[k][a] != doubling_ancestor[k][b]){
                a = doubling_ancestor[k][a];
                b = doubling_ancestor[k][b];
            }
        }
        //この段階でaとbは兄弟なので，その親を返す
        return doubling_ancestor[0][a];

    }

    int get_dist(int a, int b){
        return distance_from_root[a] + distance_from_root[b] - 2*distance_from_root[query(a, b)];
    }
};




int main(){
    int N;//木の頂点数
    cin>>N;
    Graph tree(N);
    for(int i = 0;i<N-1;i++){
        int s, t;
        cin>>s>>t;
        s--;
        t--;
        tree[s].push_back(t);
        tree[t].push_back(s);
    }

    LCA Z(tree, 0);
    /*for(int i = 0;i<N;i++){
        cout<<i+1<<"と"<<1<<"の距離は"<<Z.get_dist(i, 0)<<endl;
    }*/
    int Q;
    for(int j = 0;j<Q;j++){
        int K;
        cin>>K;

        vector<int> V(K);
        for(int i = 0;i<K;i++){
            cin>>V[i];
            V[i]--;
        }


    }
    return 0;
}