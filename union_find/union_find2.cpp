#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pil = pair<int, ll>;

class Union_find {
    int N;
    vector<int> parent;  // parent[x] = ノードxの親
    vector<int> height;  // height[x] = xの下の木の高さ
    vector<int> comp_size;
    int num_of_components;

    int comp(int x) {  // xの属する成分（木の根）を求める
        if (parent[x] == x) return x;

        parent[x] = comp(parent[x]);
        return parent[x];
    }

   public:
    Union_find(int n) {
        N = n;
        parent.resize(N);
        height.assign(N, 0);
        comp_size.assign(N, 1);
        num_of_components = N;
        for (int i = 0; i < N; i++) {
            parent[i] = i;
        }
    }

    void unite(int x, int y) {  // xとyを繋げる
        x = comp(x);
        y = comp(y);

        if (x == y) return;

        if (height[x] < height[y]) {
            parent[x] = y;
            comp_size[y] += comp_size[x];
        } else {
            parent[y] = x;
            comp_size[x] += comp_size[y];

            if (height[x] == height[y]) height[x]++;
        }
        num_of_components--;
    }

    bool same(int x, int y) {
        return comp(x) == comp(y);
    }

    int size(int x) {
        return comp_size[comp(x)];
    }

    int root(int x) {
        return comp(x);
    }

    int get_num_of_components() {
        return num_of_components;
    }
};

int main() {
    int N, Q;
    cin >> N >> Q;

    Union_find Z(N);
    for (int i = 0; i < Q; i++) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 1) {
            cout << (int)Z.same(x, y) << endl;
        } else {
            Z.unite(x, y);
        }
    }
}