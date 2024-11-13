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

double len(Point a, Point b) {
    double res = std::sqrt((double)((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
    return res;
}
double getDia(std::vector<Point> p) { // 旋转卡壳, max
    double res = 0;
    if (p.size() == 2) {
        return len(p[0], p[1]);
    }
    std::vector<Point> S(p);
    S.push_back(p[0]);
    int j = 2;
    for (int i = 0; i < S.size() - 1; i ++) {
        while (cross(S[i + 1] - S[i], S[j] - S[i]) < cross(S[i + 1] - S[i], S[j + 1] - S[i])) {
            j = (j + 1) % (S.size() - 1); 
        }
        res = std::max({res, len(S[i], S[j]), len(S[i + 1], S[j])});
    }
    return res;
}
const double pi = acos(-1.0);
void solve() {
    int n;
    std::cin >> n;
    std::vector<Point> p(n);
    for (int i = 0; i < n; i ++) {
        std::cin >> p[i].x >> p[i].y;
    }
    auto it = getHull(p);
    int siz = it.size();
    double ans = 0;
    for (int i = 1; i < siz; i ++) {
        ans += len(it[i - 1], it[i]);
    }
    ans += len(it[0], it[siz - 1]);
    // A's C
    // B's d
    int m;

    std::cin >> m;
    std::vector<Point> q(m);
    for (int i = 0; i < m; i ++) {
        std::cin >> q[i].x >> q[i].y;
    }
    auto itr = getHull(q);
    ans += 2 * getDia(itr) * pi;
    std::cout << std::fixed << std::setprecision(15) << ans << '\n';
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}