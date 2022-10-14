#include <bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
using namespace std;
using pii=pair<int,int>;

using Graph = vector<vector<int>>;

template<typename T> class Dinic{
    struct edge{
        int to;
        T cap;
        int rev;
    };

    const T INF = std::numeric_limits<T>::max();
    int V;
    vector<vector<edge>> network;
    vector<vector<edge>> tmp_network;
    vector<int> distance;
    vector<int> memo;
    
    void init_tmp_network(){
        tmp_network.assign(network.size(), {});
        for(int v = 0;v<network.size();v++){
            for(auto e : network[v]){
                tmp_network[v].push_back(e);
            }
        }
    }

    void add_edge(int _from, int _to, T _cap){
        edge e, e_reverse;
        e.to = _to;
        e.cap = _cap;
        e.rev = network[_to].size();
        //network[e.to][e.rev]=eの逆辺
        e_reverse.to = _from;
        e_reverse.cap = 0;
        e_reverse.rev = network[_from].size();
        network[_from].push_back(e);
        network[_to].push_back(e_reverse);
    }

    void bfs(int s){
        //使える辺を使ってsからの距離をbfs
        
        distance.assign(V, -1);
        distance[s] = 0;
        queue<int> to_do;
        to_do.push(s);
        while(!to_do.empty()){
            int v = to_do.front();
            to_do.pop();
            for(auto e : tmp_network[v]){
                if(e.cap > 0 && distance[e.to] < 0){
                    distance[e.to] = distance[v] + 1;
                    to_do.push(e.to);
                }
            }
        }
    }

    T dfs(int s, int t, T f){
        if(s == t) return f;
        for(int i = memo[s];i<tmp_network[s].size();i++){
            memo[s] = i;
            //sスタートの頂点はi-1番目までは通れなかったことをメモ
            edge e = tmp_network[s][i];
            if(e.cap>0 && distance[s]<distance[e.to]){
                //eが通れるとき
                T d = dfs(e.to, t, min(f, e.cap));
                //通った辺の流量を更新（e.capを更新してはいけない！network[s][i].capを直接更新せよ．）
                if(d > 0){
                    tmp_network[s][i].cap -= d;
                    tmp_network[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    

public:

    Dinic(vector<vector<pair<int, T>>> &G){
        V = G.size();
        network.resize(V);
        for(int v = 0;v<V;v++){
            for(auto p : G[v]){
                int _from, _to;
                T _cap;
                _from = v;
                tie(_to, _cap) = p;
                add_edge(_from, _to, _cap);
            }
        }
    }

    T solve(int s, int t){//sからtへの最大フローを返す
        init_tmp_network();
        T flow = 0;
        T f = 0;
        //int count = 0;
        while(true){
            bfs(s);
            //cout<<"bfs : "<<count<<endl;
            //count++;

            //if(count>1000) break;
            if(distance[t]<0) return flow;
            memo.assign(V, 0);
            f = dfs(s, t, INF);
            //cout<<f<<endl;
            while(f > 0){
                flow += f;
                f = dfs(s, t, INF);
            }
        }
        return 0;
    }

};

int main() {
    int V,E;
    cin>>V>>E;
    vector<vector<pair<int,int>>> adj_list(V);
    for(int i = 0;i<E;i++){
        int u, v, c;
        cin>>u>>v>>c;
        adj_list[u].push_back(make_pair(v, c));
    }

    Dinic<int> Z(adj_list);

    cout<<Z.solve(0, V - 1)<<endl;
    return 0;
}