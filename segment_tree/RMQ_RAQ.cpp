#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; i++)
#define all(v) (v).begin(), (v).end()

//区間の最小値を取得，区間に値を加算
template <typename T>
class RMQ_RAQ {
    int n;                  //葉の数
    vector<T> binary_tree;  //完全二分木を表す配列
    // binary_tree[i] = iに対応する半開区間における配列Aの最小値
    vector<T> lazy_tree;  //遅延評価用の配列

    //ノードkの値を遅延評価（lazy_tree[k]に値が入っている時はその影響を子ノードとbinary_tree[k]の方にうつす）
    void eval(int k) {
        if (lazy_tree[k] != 0) {
            if (k < n - 1) {
                lazy_tree[2 * k + 1] += lazy_tree[k];
                lazy_tree[2 * k + 2] += lazy_tree[k];
            }
            binary_tree[k] += lazy_tree[k];
            lazy_tree[k] = 0;
        }
    }

    void update_sub(int a, int b, T x, int k, int l, int r) {
        eval(k);
        if (r <= a || b <= l) {  //[a, b)と[l, r)が交わらないとき
            return;
        } else if (a <= l && r <= b) {
            //[l, r)が[a, b)に含まれるとき，[l, r)上の値はxに更新される
            lazy_tree[k] += x;
            eval(
                k);  //（いらない？）いるっぽい（ないと下の「ここ！」のところで親の値が更新されない）
        } else {
            //包含はないが交わるとき，2人の子区間を更新
            update_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            update_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
            binary_tree[k] =
                min(binary_tree[2 * k + 1], binary_tree[2 * k + 2]);  //↑ここ！
        }
    }

    T query_sub(int a, int b, int k, int l, int r) {
        // k：いま見てるノードのindex，[l,r)：そのノードの表す区間
        //[l,r) \cap [a, b)での最小値を返す関数
        eval(k);
        if (r <= a || b <= l) {  //[a, b)と[l, r)が交わらないとき
            return INF;
        } else if (a <= l && r <= b) {
            //[l, r)が[a, b)に含まれるとき，[l, r)での最小値を返す
            return binary_tree[k];
        } else {
            //包含はないが交わるとき，2人の子区間を調べる
            T candidate_l = query_sub(a, b, 2 * k + 1, l, (l + r) / 2);
            T candidate_r = query_sub(a, b, 2 * k + 2, (l + r) / 2, r);

            return min(candidate_l, candidate_r);
        }
    }

   public:
    const T INF = std::numeric_limits<T>::max();
    //コンストラクタ
    // n_ 個の数値の配列Aに対応するRMQ_RSQを作る．n=（n_以上の最小の2べき）
    // binary_tree，lazy_treeの大きさは2n-1を超えるようにn_ * 4で初期化
    RMQ_RAQ(int n_) : n(), binary_tree(n_ * 4, 0), lazy_tree(n_ * 4, 0) {
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n = x;
    }

    void printing() {
        //木の様子を表示，デバッグ用
        int cnt = 2;
        for (int i = 0; i < 2 * n - 1; i++) {
            T b = binary_tree[i];
            T l = lazy_tree[i];
            cout << ((b != INF) ? to_string(b) : "INF") << "("
                 << ((l != INF) ? to_string(l) : "INF") << "),";
            if (i + 2 == cnt) {
                cout << endl;
                cnt *= 2;
            }
        }
    }

    // A[a]~A[b-1]の値に+xする O(log n)
    void update(int a, int b, T x) {
        update_sub(a, b, x, 0, 0, n);
        // printing();
    }

    //区間[a,b)での最小値を取得 O(log n)
    T query(int a, int b) {
        // printing();
        return query_sub(a, b, 0, 0, n);
    }

    // A[i]を取得
    T get_value(int i) {
        return query(i, i + 1);
    }
};

// verifyは https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H
int main() {
    int N, Q;
    cin >> N >> Q;
    RMQ_RAQ<int> Z(N);
    vector<int> ans;
    rep(q, Q) {
        int k;
        cin >> k;
        if (k == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            Z.update(s, t + 1, x);
        } else {
            int s, t;
            cin >> s >> t;
            ans.push_back(Z.query(s, t + 1));
        }
    }
    for (auto x : ans) {
        cout << x << endl;
    }
    return 0;
}
