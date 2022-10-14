#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pil = pair<int, ll>;

class Union_find{
    int N;
    vector<int> parent;//parent[x] = ノードxの親
    vector<int> height;//height[x] = xの下の木の高さ

    int comp(int x){//xの属する成分（木の根）を求める
        if(parent[x] == x) return x;

        parent[x] = comp(parent[x]);
        return parent[x];
    }

public:
    Union_find(){}
    Union_find(int n){
        N = n;
        parent.resize(N);
        height.assign(N, 0);
        for(int i = 0;i<N;i++){
            parent[i] = i;
        }
    }

    void unite(int x, int y){//xとyを繋げる
        x = comp(x);
        y = comp(y);

        if(x == y) return;

        if(height[x] < height[y]){
            parent[x] = y;
        }else{
            parent[y] = x;
            if(height[x] == height[y]) height[x]++;
        }
    }

    bool same(int x, int y){
        return comp(x) == comp(y);
    }
};

template<typename T> struct edge{
    T v1;
    T v2;
    T cost;

    edge(){}

    edge(T _v1, T _v2, T _cost){
        v1 = _v1;
        v2 = _v2;
        cost = _cost;
    }
};

template<typename T> bool compare(const edge<T> &e1, const edge<T> &e2){
    return e1.cost < e2.cost;
}

template<typename T> class Kruskal{
    int N;
    T total_cost;
    vector<edge<T>> Tree;

public:
    
    Kruskal(vector<edge<T>> &G, int n){//O(E log E)
        N = n;
        Tree.resize(N);
        sort(G.begin(), G.end(), compare<T>);
        Union_find Z(N);
        total_cost = 0;
        for(auto e : G){
            if(!Z.same(e.v1, e.v2)){
                Z.unite(e.v1, e.v2);
                total_cost += e.cost;
            }
        }
    }
    T sum(){
        return total_cost;
    }
    vector<edge<T>> tree{
        return Tree;
    }

};

int main(){
    int V, E;
    cin>>V>>E;

    vector<edge<int>> G;
    for(int i = 0;i<E;i++){
        int s, t, w;
        cin>>s>>t>>w;
        G.emplace_back(s, t, w);
    }

    Kruskal<int> Z(G, V);

    cout<<Z.sum()<<endl;

    return 0;
}