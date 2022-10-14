#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pil = pair<int, ll>;
#define rep(i, n) for (int i = 0; i < n; i++)
class tsort {
   public:
    int V;
    vector<vector<int>> G;
    vector<int> deg, res;
    tsort(int node_size) : V(node_size), G(V), deg(V, 0) {
    }
    void add_edge(int from, int to) {
        G[from].push_back(to);
        deg[to]++;
    }
    bool solve() {
        // DAG かどうか(true / false) を返し, true
        // ならresにトポロジカル順序にソートされた頂点列が格納される.
        // O(V+E)
        queue<int> que;
        for (int i = 0; i < V; i++) {
            if (deg[i] == 0) {
                que.push(i);
            }
        }
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            res.push_back(p);
            for (int v : G[p]) {
                if (--deg[v] == 0) {
                    que.push(v);
                }
            }
        }
        return (*max_element(deg.begin(), deg.end()) == 0);
    }
};
