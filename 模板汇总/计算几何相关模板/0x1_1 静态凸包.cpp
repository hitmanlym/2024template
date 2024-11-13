#include<bits/stdc++.h>
using i64 = double;

struct Point {
    i64 x;
    i64 y;
    Point(i64 x = 0, i64 y = 0) : x(x), y(y) {}
};

bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

Point operator+(const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator-(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

i64 dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

i64 cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

void norm(std::vector<Point> &h) {
    int i = 0;
    for (int j = 0; j < int(h.size()); j++) {
        if (h[j].y < h[i].y || (h[j].y == h[i].y && h[j].x < h[i].x)) {
            i = j;
        }
    }
    std::rotate(h.begin(), h.begin() + i, h.end());
}

int sgn(const Point &a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 0 : 1;
}

std::vector<Point> getHull(std::vector<Point> p) {
    std::vector<Point> h, l;
    std::sort(p.begin(), p.end(), [&](auto a, auto b) {
        if (a.x != b.x) {
            return a.x < b.x;
        } else {
            return a.y < b.y;
        }
    });
    p.erase(std::unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) {
        return p;
    }
    
    for (auto a : p) {
        while (h.size() > 1 && cross(a - h.back(), a - h[h.size() - 2]) <= 0) {
            h.pop_back();
        }
        while (l.size() > 1 && cross(a - l.back(), a - l[l.size() - 2]) >= 0) {
            l.pop_back();
        }
        l.push_back(a);
        h.push_back(a);
    }
    
    l.pop_back();
    std::reverse(h.begin(), h.end());
    h.pop_back();
    l.insert(l.end(), h.begin(), h.end());
    return l;
}
int lt(i64 a, i64 b) {
    if (a < b) return 1;
    else return 0;
}
// 极角排序

int quater(Point p) { // 0, 1, 2, 3
    return lt(p.y, 0ll) << 1 | lt(p.x, 0ll) ^ lt(p.y, 0ll);
}
void psort(std::vector<Point> &p, Point o = {0, 0}) {
    std::sort(p.begin(), p.end(), [&](auto p1, auto p2) {
        return quater(p1 - o) < quater(p2 - o) || 
            quater(p1 - o) == quater(p2 - o) && lt(0, cross(p1 - o, p2 - o));
    });
}
void solve() {
    int n;
    std::cin >> n;
    std::vector<Point> p(n);
    for (int i = 0; i < n; i ++) {
        std::cin >> p[i].x >> p[i].y;
    }
    auto it = getHull(p);
    double ans = 0;
    int siz = it.size();
    auto len = [&](i64 a, i64 b, i64 c, i64 d) -> double {
        double res = std::sqrt((double)((c - a) * (c - a) + (d - b) * (d - b)));
        return res;
    };
    for (int i = 1; i < siz; i ++) {
        ans += len(it[i - 1].x, it[i - 1].y, it[i].x, it[i].y);
    }
    ans += len(it[0].x, it[0].y, it[siz - 1].x, it[siz - 1].y);
    printf("%.2lf\n", ans);
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}