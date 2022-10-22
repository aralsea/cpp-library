#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pil = pair<int, ll>;

template <typename T>
class LIS {
    const T INF = std::numeric_limits<T>::max();
    const T minus_INF = std::numeric_limits<T>::min();

    int N;
    vector<T> array;
    vector<int> length;  // length[i] = A[0]~A[i]のLISの長さ
    vector<T> memo;  // memo[i]=長さiの狭義増加部分列の右端の値の最小値
    int right_pos;  // memoのうち，INFでない最も右の位置

    void solve() {
        for (int i = 0; i < N; i++) {
            auto itr = lower_bound(
                memo.begin(), memo.end(),
                array
                    [i]);  //広義増加にしたいときはここをupper_boundに変更する！
            int pos = distance(memo.begin(), itr);
            memo[pos] = min(memo[pos], array[i]);
            right_pos = max(right_pos, pos);
            length[i] = right_pos;
        }
    }

   public:
    LIS(const vector<T> &A) {
        N = A.size();
        array = A;
        memo.assign(N + 1, INF);
        memo[0] = minus_INF;
        length.assign(N, 0);
        right_pos = 0;
        solve();
    }

    /*void set(int i, T x){
        if(i < N){
            array[i] = x;
        }
    }*/

    int get_length() {
        return length[N - 1];
    }
    int get_length(int i) {
        return length[i];
    }
};

int main() {
    // 1．入力
    int N;
    cin >> N;

    vector<ll> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    LIS<ll> Z(A);

    cout << Z.get_length(N - 1) << endl;
    return 0;
}