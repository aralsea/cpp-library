#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Dijkstra {
    using P = pair<T, int>;  // priority_queueで使う用，(距離，頂点）
    struct edge {
        int to;
        T cost;

        edge() {
        }
        edge(int _to, T _cost) {
            to = _to;
            cost = _cost;
        }
    };

    int N;
    vector<vector<edge>> G;
    vector<T> dist;

   public:
    const T INF = std::numeric_limits<T>::max();

    Dijkstra(int n) {
        N = n;
        G.resize(N);
        dist.assign(N, INF);
    }

    void add_edge(int from, int to, T cost) {
        G[from].emplace_back(to, cost);
    }

    Dijkstra(vector<vector<pair<int, T>>> &adj_list) {
        N = adj_list.size();
        G.resize(N);
        for (int from = 0; from < N; from++) {
            for (auto p : adj_list[from]) {
                int to;
                T cost;
                tie(to, cost) = p;
                add_edge(from, to, cost);
            }
        }
    }

    void init(int start) {  // O((E+V)logV)
        dist.assign(N, INF);
        priority_queue<P, vector<P>, greater<P>>
            to_do;  //（仮距離，頂点）のデータを格納

        dist[start] = 0;
        to_do.emplace(
            0,
            start);  // pushとほとんど同じだけど，Pのコンストラクタ引数を直接渡せて便利

        while (!to_do.empty()) {
            P vertex = to_do.top();
            to_do.pop();
            //頂点vへの距離が確定

            T tmp_dist_v = vertex.first;
            int v = vertex.second;

            if (tmp_dist_v != dist[v])
                continue;  // queueには同じ頂点のデータで最終更新より前の仮距離を持つものも入ってるかもしれないので，それを無視．これがないとO(V^2)

            for (edge &e : G[v]) {  // vから伸びる辺の先の頂点へ書き込み
                T new_dist_next = tmp_dist_v + e.cost;
                if (dist[e.to] > new_dist_next) {
                    dist[e.to] = new_dist_next;
                    to_do.emplace(new_dist_next, e.to);
                }
            }
        }
    }

    T get_dist(int goal) {
        return dist[goal];
    }

    T get_dist(int start, int goal) {
        init(start);
        return dist[goal];
    }
};

int main() {
    int V, E, r;
    cin >> V >> E >> r;
    vector<vector<pair<int, int>>> adj_list(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        adj_list[s].emplace_back(t, d);
    }

    Dijkstra<int> Z(adj_list);
    const int INF = std::numeric_limits<int>::max();

    Z.init(r);

    for (int v = 0; v < V; v++) {
        int ans = Z.get_dist(v);
        if (ans < INF)
            cout << ans << endl;
        else
            cout << "INF" << endl;
    }
}