#include <bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define INF 1000000007
using namespace std;
using pii=pair<int,int>;

using Graph = vector<vector<int>>;

vector<bool> already_seen;
vector<int> post_order;//post_order[i] = 順位iの頂点
vector<int> cmp;//cmp[i]=頂点iの属する強連結成分の番号
Graph G, H;//H：Gの辺を逆向きにしたグラフ

void dfs(int v){
    //帰りがけ順を記録するdfs
    already_seen[v]=true;
    for(auto next_v : G[v]){
        if(!already_seen[next_v]) dfs(next_v);
    }
    post_order.push_back(v);
}

void dfs2(int v, int cmp_number){
    already_seen[v] = true;
    cmp[v]=cmp_number;
    for(auto next_v : H[v]){
        if(!already_seen[next_v]) dfs2(next_v, cmp_number);
    }

}

Graph invert(const Graph G){
    int n = G.size();
    Graph ret(n);
    for(int v = 0;v<n;v++){
        for(auto next_v : G[v]){
            ret[next_v].push_back(v);
        }
    }
    return ret;
}
void SCC(){
    //cmpを計算,O(V+E)
    int n = G.size();
    cmp.resize(n);

    //first dfs
    already_seen.assign(n, false);
    for(int v = 0;v<n;v++){
        if(!already_seen[v]) dfs(v);
    }
    /*for(int i = 0;i<n;i++){
        cout<<i<<"番目の頂点は"<<post_order[i]<<endl;
    }*/
    //second dfs
    already_seen.assign(n, false);
    int cmp_number = 0;
    for(int i = n-1;i>=0;i--){
        int v = post_order[i];
        if(!already_seen[v]){
            dfs2(v, cmp_number);
            cmp_number++;
        }
    }
}

int main(){
    int V, E;
    cin>>V>>E;
    G.resize(V);
    H.resize(V);
    
    for(int i = 0;i<E;i++){
        int A, B;
        cin>>A>>B;
        G[A].push_back(B);
        H[B].push_back(A);
    }

    SCC();

    long long Q;
    cin>>Q;
    for(int i = 0;i<Q;i++){
        int u, v;
        cin>>u>>v;
        if(cmp[u] == cmp[v]){
            cout<<1<<endl;
        }else{
            cout<<0<<endl;
        }
    }


}