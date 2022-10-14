#include <bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
using namespace std;
using pii=pair<int,int>;

template<typename T> struct Point{
    T x;
    T y;

    Point(){}
    Point(T xx, T yy){
        x = xx;
        y = yy;
    }

    T det(Point<T> q){
        return x*q.y - y*q.x;
    }
};

template<typename T> Point<T> operator - (Point<T> p, Point<T> q){
        Point<T> ret{p.x - q.x, p.y - q.y};
        return ret;
    }

template<typename T> bool comp(Point<T> p, Point<T> q){
    if(p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}



template<typename T> 
vector<Point<T>> convex_hull(vector<Point<T>> &points){
    int N = points.size();
    if(N <= 3) return points;

    sort(points.begin(), points.end(), comp<T>);//x,yの辞書順で小さい順に整列

    int k = 0;//構築中の凸包の頂点数
    vector<Point<T>> tmp(N * 2);//構築中の凸包

    //下側凸包の作成，左下の点から下側を反時計回りに見ていく
    for(int i = 0;i<N;i++){
        while(k > 1 && (tmp[k - 1] - tmp[k - 2]).det(points[i] - tmp[k - 1]) <= 0){
            k--;
        }
        tmp[k++] = points[i];
    }

    //上側凸包の作成，右上の点から上側を反時計回りに見ていく（n-2スタートなのはpoints[n-1]が既に下側凸包の計算の最後に登場しているから）
    for(int i = N - 2, t = k; i >= 0;i--){
         while(k > t && (tmp[k - 1] - tmp[k - 2]).det(points[i] - tmp[k - 1]) <= 0){
            k--;
        }
        tmp[k++] = points[i];
    }
    tmp.resize(k - 1);//tmp[k-1]にpoints[0]がもう一度登場するので，そこは切り落とす
    return tmp;
}

int main() {
    
    return 0;
}