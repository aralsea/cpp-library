#include <algorithm>
#include <bitset>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#define REP(i, n) for (int i = 0; i < n; i++)
#define INF 100000000000007
using namespace std;
using pii = pair<int, int>;
using ll = long long;

vector<ll> fac, finv, inv;

// テーブルを作る前処理
void COMinit(ll MAX, ll MOD) {
    fac = vector<ll>(MAX);  /*n! modのデーブル　*/
    finv = vector<ll>(MAX); /*n!の逆元のテーブル*/
    inv = vector<ll>(MAX);  /*nの逆元のテーブル*/

    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (ll i = 2; i < MAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

// 二項係数計算 nCkを与える
// n = -mが負の数の場合には，負の二項係数を
//  (-m)Ck = (-1)^k (m+k-1)Ck
// により返す
ll COM(ll MOD, ll n, ll k) {
    if (0 <= n && n < k) return 0;
    if (k < 0) return 0;
    if (n >= 0) {
        return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
    } else {
        ll ret = COM(MOD, -n + k - 1, k);
        return (k % 2) ? (MOD - ret) % MOD : ret;
    }
}

ll modpow(ll MOD, ll b, ll p) {
    ll num = 1, power = b % MOD;
    if (power == 0 && p > 0) {
        return 0;
    }
    for (ll i = 0; i <= 30; i++) {
        if ((p >> i) & 1) num *= power;
        num %= MOD;
        power *= power;
        power %= MOD;
    }
    return num;
}