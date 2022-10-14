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
class SuffixArray {
    vi stupid_sa(const string &S) {
        vi sa(N + 1);
        int N = S.size();
        for (int i = 0; i <= N; i++) {
            sa[i] = i;
        }

        sort(all(sa), [&](const int &l, const int &r) {
            return S.substr(l) < S.substr(r);
        });
        return sa;
    }

   public:
    string S;
    int N;
    vi sa;
    SuffixArray(string str) : S(str), N(str.size()) {
        sa = stupid_sa(S);
    }
};
int main() {
    string S;
    cin >> S;
    int N = S.size();

    SuffixArray Z(S);
    for (int i = 0; i <= N; i++) {
        cout << Z.sa[i] << " ";
    }
    cout << endl;
}