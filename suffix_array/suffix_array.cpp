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
    vi sa_is(const vi &S, const int K) {
        //数字の種類数がkの数列Sのsuffix arrayをO(|S|)で計算する
        const int N = S.size();

        // step 1. S, L, LMSを計算
        vector<bool> is_S(N + 1, false);
        vector<bool> is_LMS(N + 1, false);
        vi LMSs;

        is_S[N] = true;
        is_LMS[N] = true;

        for (int i = N - 2; i >= 0; i--) {
            is_S[i] = (S[i] < S[i + 1]) || (S[i] == S[i + 1] && is_S[i + 1]);
        }
        for (int i = 1; i <= N; i++) {
            is_LMS[i] = (is_S[i] && !is_S[i - 1]);
            if (is_LMS[i]) {
                LMSs.push_back(i);
            }
        }
        cout << "LMSs = ";
        for (int x : LMSs) {
            cout << x << " ";
        }
        cout << endl;
        // step 2. 1回目のinduced sort
        cout << "first induced sort" << endl;
        vi first_sa = induced_sort(S, LMSs, is_S, K);

        // step 3. LMSsを辞書順ソート
        vi ordered_LMSs(LMSs.size());  // first_saにおけるLMSの並び
        int l = 0;
        for (int idx : first_sa) {
            if (is_LMS[idx]) {
                ordered_LMSs[l++] = idx;
            }
        }
        cout << "orderd_LMSs = ";
        for (int x : ordered_LMSs) {
            cout << x << " ";
        }
        cout << endl;

        // LMS substring に rank をつけていく
        // first_saのLMS以外の部分はもういらないので再利用
        first_sa[ordered_LMSs[0]] = 0;  // Nのrankは0
        int rank = 0;
        if (ordered_LMSs.size() > 1) {
            first_sa[ordered_LMSs[1]] = ++rank;
        }
        for (int i = 2; i < ordered_LMSs.size(); i++) {
            int p = ordered_LMSs[i - 1];
            int q = ordered_LMSs[i];
            bool diff = false;
            for (int j = 0; j < N; j++) {
                if (S[p + j] != S[q + j] || (is_LMS[p + j] != is_LMS[q + j])) {
                    diff = true;
                    break;
                }
                if (j > 0 && (is_LMS[p + j] || is_LMS[q + j])) {
                    break;
                }
            }
            if (diff) {
                rank++;
            }
            first_sa[ordered_LMSs[i]] = rank;
        }

        vi sorted_LMSs;  //正しくソートされたLMSの配列
        if (rank + 1 == LMSs.size()) {
            sorted_LMSs = ordered_LMSs;
            cout << "sorted_LMSs = ";
            for (int x : sorted_LMSs) {
                cout << x << " ";
            }
            cout << endl;
        } else {
            // LMS substringを1文字とみた配列を作成
            vi small_S(ordered_LMSs.size());
            l = 0;
            for (int i = 0; i <= N; i++) {
                if (is_LMS[i]) {
                    small_S[l++] = first_sa[i];
                }
            }
            cout << "small_S = ";
            for (int x : small_S) {
                cout << x << " ";
            }
            cout << endl;
            sorted_LMSs = sa_is(small_S, rank + 1);
            cout << "sorted_LMSs = ";
            for (int x : sorted_LMSs) {
                cout << x << " ";
            }
            cout << endl;
            for (int &x : sorted_LMSs) {
                if (x == LMSs.size()) continue;
                x = LMSs[x];
            }
            sorted_LMSs.erase(sorted_LMSs.begin());
            cout << "sorted_LMSs, fixed = ";
            for (int x : sorted_LMSs) {
                cout << x << " ";
            }
            cout << endl;
        }

        // step 4. もう一度induced sortする
        cout << "second induced sort" << endl;
        return induced_sort(S, sorted_LMSs, is_S, K);
    };

    vi induced_sort(const vi &S, const vi &LMSs, const vector<bool> &is_S,
                    const int K) {
        //指定されたLMSの並びLMSsに従ってinduced sortを行う
        // Sは0~K-1の数字からなる配列
        const int N = S.size();

        vi SA(N + 1, -1);  //結果を格納する配列
        vi chars(
            K + 1,
            0);  // chars[c] = 0からc-1までの数字がいくつあるか，という累積和
        vi count_L(K, 0);
        for (int i = 0; i < N; i++) {
            count_L[S[i]] += !is_S[i];
        }
        for (int c : S) {
            chars[c + 1]++;
        }
        for (int c = 1; c <= K; c++) {
            chars[c] += chars[c - 1];
        }
        vi count(K, 0);  // count[c] = 文字cのbinがいくつ埋まっているか

        // step 1，LMSsの元を逆順にした上でSAの後ろから入れる
        SA[0] = N;
        for (int i = LMSs.size() - 1; i >= 0; i--) {
            if (LMSs[i] == N) continue;
            int c = S[LMSs[i]];
            SA[chars[c + 1] - count[c]++] = LMSs[i];
        }

        // output
        int cc = 0;
        int res_L = 0;
        for (int i = 0; i <= N; i++) {
            cout << setw(2) << i << " ";
            if (i == 0) {
                cout << "$ S : ";
            } else {
                while (i > chars[cc + 1]) {
                    cc++;
                    res_L = count_L[cc];
                }
                cout << char(cc + 'a') << " ";
                if (res_L > 0) {
                    cout << "L : ";
                    res_L--;
                } else {
                    cout << "S : ";
                }
            }

            if (SA[i] == -1) {
                cout << "--" << endl;
            } else {
                cout << setw(2) << SA[i] << " ";
                for (int j = SA[i]; j < N; j++) {
                    cout << char(S[j] + 'a');
                }
                cout << "$" << endl;
            }
        }
        cout << endl;

        // step 2. SAを前から見ていって，L型のidxをSAの先頭から入れていく
        count.assign(K, 0);
        for (int i = 0; i <= N; i++) {
            //今見てるSA[i]が空(=-1)or先頭idx(=0)なら次へ
            if (SA[i] == -1 || SA[i] == 0) continue;

            //今見てるSA[i]のひとつ左のidxを調べる
            if (is_S[SA[i] - 1]) continue;
            int c = S[SA[i] - 1];
            SA[chars[c] + 1 + count[c]] = SA[i] - 1;
            count[c]++;
        }

        // output
        cc = 0;
        res_L = 0;
        for (int i = 0; i <= N; i++) {
            cout << setw(2) << i << " ";
            if (i == 0) {
                cout << "$ S : ";
            } else {
                while (i > chars[cc + 1]) {
                    cc++;
                    res_L = count_L[cc];
                }
                cout << char(cc + 'a') << " ";
                if (res_L > 0) {
                    cout << "L : ";
                    res_L--;
                } else {
                    cout << "S : ";
                }
            }

            if (SA[i] == -1) {
                cout << "--" << endl;
            } else {
                cout << setw(2) << SA[i] << " ";
                for (int j = SA[i]; j < N; j++) {
                    cout << char(S[j] + 'a');
                }
                cout << "$" << endl;
            }
        }
        cout << endl;

        // step 3. SAを後ろから見ていって，S型のidxを後ろから入れていく
        count.assign(K, 0);
        for (int i = N; i >= 0; i--) {
            //今見てるSA[i]が空(=-1)or先頭idx(=0)なら次へ
            if (SA[i] == -1 || SA[i] == 0) continue;

            //今見てるSA[i]のひとつ左のidxを調べる
            if (!is_S[SA[i] - 1]) continue;
            int c = S[SA[i] - 1];
            SA[chars[c + 1] - count[c]++] = SA[i] - 1;
        }

        // output
        cc = 0;
        res_L = 0;
        for (int i = 0; i <= N; i++) {
            cout << setw(2) << i << " ";
            if (i == 0) {
                cout << "$ S : ";
            } else {
                while (i > chars[cc + 1]) {
                    cc++;
                    res_L = count_L[cc];
                }
                cout << char(cc + 'a') << " ";
                if (res_L > 0) {
                    cout << "L : ";
                    res_L--;
                } else {
                    cout << "S : ";
                }
            }

            if (SA[i] == -1) {
                cout << "--" << endl;
            } else {
                cout << setw(2) << SA[i] << " ";
                for (int j = SA[i]; j < N; j++) {
                    cout << char(S[j] + 'a');
                }
                cout << "$" << endl;
            }
        }
        cout << endl;

        return SA;
    }

   public:
    string S;
    int N;
    vi sa;
    SuffixArray(string str) : S(str), N(str.size()) {
        vi VS(N);
        for (int i = 0; i < N; i++) {
            VS[i] = S[i] - 'a';
        }
        sa = sa_is(VS, 26);
    }
};

class StupidSuffixArray {
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
    StupidSuffixArray(string str) : S(str), N(str.size()) {
        sa = stupid_sa(S);
    }
};
int main() {
    /*int M = 15;
    vector<string> str;
    str.push_back("");
    for (int x = 1; x <= M; x++) {
        cout << "length " << x << " strings..." << endl;
        vector<string> new_str;
        for (int y = 0; y < 10; y++) {
            for (string t : str) {
                string S = t + char('a' + y);
                int N = S.size();

                SuffixArray Z(S);
                StupidSuffixArray W(S);
                bool is_ok = true;
                for (int i = 0; i <= N; i++) {
                    if (Z.sa[i] != W.sa[i]) {
                        is_ok = false;
                        cout << "Failed for " << S << endl;
                        break;
                    }
                }
                if (is_ok) {
                    // cout << "OK for " << S << endl;

                } else {
                    cout << "Suffix array" << endl;
                    for (int i = 0; i <= N; i++) {
                        cout << setw(2) << i << " ";
                        cout << S.substr(Z.sa[i]) << "$ ";
                        if (Z.sa[i] != W.sa[i]) {
                            cout << "<-" << endl;
                        } else {
                            cout << endl;
                        }
                    }
                    cout << endl;

                    cout << "Stupid Suffix array" << endl;
                    for (int i = 0; i <= N; i++) {
                        cout << setw(2) << i << " ";
                        cout << S.substr(W.sa[i]) << "$ ";
                        if (Z.sa[i] != W.sa[i]) {
                            cout << "<-" << endl;
                        } else {
                            cout << endl;
                        }
                    }
                    return 0;
                }
                new_str.push_back(S);
            }
        }
        str = new_str;
    }*/
    string S = "bababac";
    int N = S.size();

    SuffixArray Z(S);
    StupidSuffixArray W(S);
    bool is_ok = true;
    for (int i = 0; i <= N; i++) {
        if (Z.sa[i] != W.sa[i]) {
            is_ok = false;
            cout << "Failed for " << S << endl;
            break;
        }
    }
    if (is_ok) {
        cout << "OK for " << S << endl;
    } else {
        cout << "Suffix array" << endl;
        for (int i = 0; i <= N; i++) {
            cout << setw(2) << i << " ";
            cout << S.substr(Z.sa[i]) << "$ ";
            if (Z.sa[i] != W.sa[i]) {
                cout << "<-" << endl;
            } else {
                cout << endl;
            }
        }
        cout << endl;

        cout << "Stupid Suffix array" << endl;
        for (int i = 0; i <= N; i++) {
            cout << setw(2) << i << " ";
            cout << S.substr(W.sa[i]) << "$ ";
            if (Z.sa[i] != W.sa[i]) {
                cout << "<-" << endl;
            } else {
                cout << endl;
            }
        }
    }
    /*for (int i = 0; i <= N; i++) {
        cout << i << " ";
        cout << S.substr(Z.sa[i], S.size() - Z.sa[i]) << "$" << endl;
    }*/

    /*int Q;
    cin >> Q;
    vi ans(Q);
    rep(q, Q) {
        string P;
        cin >> P;

        // PがSの中にあるかどうか
        // S[SA[left]: ]（の先頭|P|文字分）<=P<S[SA[right]:]となるleft,
        // rightを二分探索で決定
        int left = 0, right = N + 1;
        while (right - left > 1) {
            int mid = left + (right - left) / 2;
            // S[SA[mid]: ]とPの大小を比較
            if (S.substr(Z.sa[mid], P.size()) <= P) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (left >= N + 1 || left == 0) {
            ans[q] = 0;
        } else if (S.substr(Z.sa[left], P.size()) == P) {
            ans[q] = 1;
        } else {
            ans[q] = 0;
        }
    }

    for (int a : ans) {
        cout << a << endl;
    }*/
}