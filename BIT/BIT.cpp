#include <bits/stdc++.h>
using namespace std;
#define INF 1000000007
#define REP(i, n) for (int i = 0; i < n; i++)
using ll = long long;
using pii = pair<int, int>;

// binary indexed tree
// BIT Zは長さNの配列
// Z[i]+=x がO(log N)
// Z[0]+Z[1]+...+Z[k]がO(log N)
// cf. 普通の配列だとそれぞれO(1),O(N)
// cf. 累積和だとそれぞれO(N),O(1)
class BIT {
    int _size = 1;
    vector<ll> bit;

   public:
    BIT(int size) : _size(size) {
        bit.assign(_size + 1, 0);
    }

    void add(int position, ll x) {
        position++;  // 1-indexed
        while (position <= _size) {
            bit[position] += x;
            position += (position & (-position));
        }
    }

    ll sum(int position) {
        // Z[0]+...+Z[position]
        position++;
        ll s = 0;
        while (position > 0) {
            s += bit[position];
            position -= (position & (-position));
        }
        return s;
    }

    ll sum(int left, int right) {
        // Z[left]+...+Z[right]
        if (left > right) {
            return 0;
        }
        return sum(right) - sum(left - 1);
    }
};

int main() {
    int N = 1000;
    BIT Z(N + 5);
    Z.add(1, 15);               // Z[1]+=15;
    cout << Z.sum(10) << endl;  // Z[0]+...+Z[10]
    cout << Z.sum(0) << endl;   // Z[0]

    return 0;
}