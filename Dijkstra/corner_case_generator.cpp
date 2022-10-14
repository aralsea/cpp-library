#include <bits/stdc++.h>
using namespace std;

int TYPE = 1;          // 1:continue忘れ, 2:最大ヒープ, 3:最大ヒープ２, 4:負辺  
int MAX_N = 2e5;       // 頂点数の最大値
int MAX_M = 2e5;       // 辺数の最大値
int MIN_C = 1;         // 辺のコストの最小値
int MAX_C = 1e9;       // 辺のコストの最大値
bool DIRECTED = false; // 有向かどうか
bool V1_TO_Vn = false; // s=1, t=n とするかどうか
bool REVERSE = false;  // tを始点としたときの撃墜ケース
int INDEXED = 1;       // 0-indexed なら 0 にする


struct Graph {
  int n, m, s, t;
  struct Edge {
    int a, b, cost;
    Edge() {}
    Edge(int a, int b, int cost): a(a), b(b), cost(cost) {}
  };
  vector<Edge> es;
  Graph() {}
  Graph(int n, int s, int t): n(n), m(0), s(s), t(t) {}
  void addEdge(int a, int b, int cost) {
    if (!DIRECTED && a > b) swap(a, b);
    es.emplace_back(a, b, cost);
    ++m;
  }
  void reverse() {
    swap(s, t);
    s = n-1-s; t = n-1-t;
    for (auto& e : es) {
      swap(e.a, e.b);
      e.a = n-1-e.a;
      e.b = n-1-e.b;
    }
  }
  void output() {
    if (V1_TO_Vn) printf("%d %d\n", n, m);
    else printf("%d %d %d %d\n", n, m, s+INDEXED, t+INDEXED);
    for (Edge& e : es) {
      printf("%d %d %d\n", e.a+INDEXED, e.b+INDEXED, e.cost);
    }
  }
};

Graph genContinue() {
  int n = MAX_N;
  n = min(n, MAX_M/2+2);
  assert(n >= 4);
  assert(MIN_C+(n-4)*2 <= MAX_C);
  int s = 0, t = n-1;
  Graph g(n, s, t);
  for (int i = 0; i < n-3; ++i) {
    g.addEdge(s, i+1, MIN_C+i);
    g.addEdge(i+1, t-1, MAX_C-i*2);
  }
  g.addEdge(t-1, t, MAX_C);
  return g;
}

Graph genMaxHeap1() {
  int chain = 0;
  while ((1ll<<chain)+MIN_C*2 <= MAX_C) ++chain;
  assert(chain >= 1);
  int way = (MAX_N-2)/(chain*2);
  way = min(way, MAX_M/(chain*3+1));
  assert(way >= 1);
  int n = way*(chain*2) + 2;
  int s = 0, t = n-1;
  Graph g(n, s, t);
  int v = 1;
  for (int i = 0; i < way; ++i) {
    int pv = s;
    for (int j = chain-1; j >= 0; --j) {
      g.addEdge(pv, v+j, (1<<j)+MIN_C*2);
      g.addEdge(pv, v+chain+j, MIN_C);
      g.addEdge(v+chain+j, v+j, MIN_C);
      pv = v+j;
    }
    g.addEdge(v, t, MAX_C);
    v += chain*2;
  }
  return g;
}

Graph genMaxHeap2() {
  int n = 0;
  while ((1ll<<n)-1+MIN_C*n <= MAX_C) ++n;
  n = min(n, MAX_N);
  assert(n >= 2);
  int s = 0, t = n-1;
  Graph g(n, s, t);
  vector<int> p;
  for (int i = 0; i < n-1; ++i) p.push_back((1<<i)+MIN_C*i);
  reverse(p.begin(), p.end());
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      g.addEdge(i, j, p[i]-p[j-1]+MIN_C);
    }
  }
  return g;
}

Graph genNegative() {
  int chain = 0;
  while ((1ll<<chain) <= MAX_C) ++chain;
  assert(chain >= 1);
  int n = chain*2+1;
  n = min(n, (MAX_N-1)/2*2+1);
  assert(3 <= n);
  int s = 0, t = n-1;
  Graph g(n, s, t);
  for (int i = n/2-1; i >= 0; --i) {
    int v = (n/2-i-1)*2;
    g.addEdge(v, v+2, 1<<i);
    g.addEdge(v, v+1, (2<<i)+i);
    g.addEdge(v+1, v+2, -((2<<i)+i));
  }
  return g;
}

int main() {
  Graph g;
  switch (TYPE) {
    case 1: g = genContinue(); break;
    case 2: g = genMaxHeap1(); break;
    case 3: g = genMaxHeap2(); break;
    case 4: g = genNegative(); break;
  }
  if (REVERSE) g.reverse();
  g.output();
  return 0;
}