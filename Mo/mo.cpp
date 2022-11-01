#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pll = pair<ll, ll>;
using Graph = vector<vector<int>>;
using vi = vector<int>;
using vl = vector<ll>;
using vs = vector<string>;
#define rep(i, n) for (int i = 0; i < n; i++)
#define all(v) (v).begin(), (v).end()

//区間の拡大縮小がO(a)のとき計算量はO(max(aN \sqrt{Q}, Q log Q)
class Mo {
    const int N;
    vector<pair<int, int>> lr;

   public:
    Mo(int n) : N(n) {
    }
    void add_query(int l, int r) {
        /*区間[l, r)へのクエリを追加*/
        lr.emplace_back(l, r);
    }

    // AL = 関数add_left()の型
    template <typename AL, typename AR, typename EL, typename ER, typename O>
    void perform(const AL &add_left, const AR &add_right, const EL &erase_left,
                 const ER &erase_right, const O &out) {
        /*
        add_left(l) = [l, r)についての情報から[l+1,
        r)についての情報を計算する処理
        out(q) =
        q番目のクエリの計算結果をメモする処理
        */
        int q = (int)lr.size();
        int bs = N / min<int>(N, sqrt(q));  // bs = [\sqrt{q}]
        vector<int> ord(q);
        iota(begin(ord), end(ord), 0);  // ord[i] = iと同じ
        sort(begin(ord), end(ord), [&](int a, int b) {
            int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
            if (ablock != bblock) return ablock < bblock;
            return (ablock & 1) ? lr[a].second > lr[b].second
                                : lr[a].second < lr[b].second;
        });
        int l = 0, r = 0;
        for (auto idx : ord) {
            while (l > lr[idx].first) add_left(--l);
            while (r < lr[idx].second) add_right(r++);
            while (l < lr[idx].first) erase_left(l++);
            while (r > lr[idx].second) erase_right(--r);
            out(idx);
        }
    }

    template <typename A, typename E, typename O>
    void perform(const A &add, const E &erase, const O &out) {
        perform(add, add, erase, erase, out);
    }
};

// verity ABC174-F https://atcoder.jp/contests/abc174/tasks/abc174_f
//種類数クエリ
int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    rep(i, N) {
        cin >> A[i];
        A[i]--;
    }

    Mo Z(N);
    rep(q, Q) {
        int L, R;
        cin >> L >> R;
        L--, R--;
        Z.add_query(L, R + 1);
    }

    vector<int> ans(Q);
    int num = 0;
    vector<int> count(N);

    auto add = [&](int i) {
        if (count[A[i]]++ == 0) num++;
    };

    auto erase = [&](int i) {
        if (--count[A[i]] == 0) num--;
    };

    auto out = [&](int q) { ans[q] = num; };

    Z.perform(add, erase, out);

    rep(q, Q) {
        cout << ans[q] << endl;
    }
}