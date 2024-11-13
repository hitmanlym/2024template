#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int inf = 9e18;
using pii = std::array<int, 2>;
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
    std::vector<Point> a(n);
    std::map<pii, bool> mp;
    for (int i = 0; i < n; i ++) {
    	std::cin >> a[i].x >> a[i].y;
    }	
    auto p = getHull(a);
    Point O = {0, 0};
    int ans = 0;
    for (int i = 0; i < p.size(); i ++) {
    	mp[(pii){p[i].x, p[i].y}] = 1;
    	if (i == p.size() - 1) {
    		ans += cross(p[i], p[0]); 
    	} else {
    		ans += cross(p[i], p[i + 1]);
    	}
    }
    ans = std::abs(ans);
    std::vector<Point> b;
    for (int i = 0; i < n; i ++) {
    	if (! mp[(pii){a[i].x, a[i].y}]) {
    		b.push_back(a[i]);
    	}
    }
    if (! b.size()) {
    	std::cout << -1 << '\n';
    	return ;
    }
    // for (auto it : p) {
    // 	std::cout << it.x << ' ' << it.y << '\n';
    // }
    // std::cout << '\n';

    auto y = getHull(b);
    // for (auto it : y) {
    // 	std::cout << it.x << ' ' << it.y << '\n';
    // }
    // std::cout << '\n';
    // std::cout << ans << '\n';

    int siz = p.size();
    // for (int i = 0; i < siz; i ++) {
    // 	p.push_back(p[i]);
    // }
    p.push_back(p[0]);
    int j = 0, M = inf;
    for (int i = 0; i < y.size(); i ++) {
    	int U = std::abs(cross((Point){y[i].x - p[0].x, y[i].y - p[0].y}, (Point){y[i].x - p[1].x, y[i].y - p[1].y}));
    	if (U < M) {
    		M = U;
    		j = i;
    	}
    }
    int oz = y.size();
    y.push_back(y[0]);
   	for (int i = 0; i < p.size() - 1; i ++) {
   		while (std::abs(cross((Point){y[j].x - p[i].x, y[j].y - p[i].y}, (Point){y[j].x - p[i + 1].x, y[j].y - p[i + 1].y}))
   			> std::abs(cross((Point){y[j + 1].x - p[i].x, y[j + 1].y - p[i].y}, (Point){y[j + 1].x - p[i + 1].x, y[j + 1].y - p[i + 1].y}))) {
   			j = (j + 1) % oz;
   		}
   		M = std::min(M, std::abs(cross((Point){y[j].x - p[i].x, y[j].y - p[i].y}, (Point){y[j].x - p[i + 1].x, y[j].y - p[i + 1].y})));
   	}
   	std::cout << ans - M << '\n';
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}
/*

2
6 
-2 0
1 -2
5 2
0 4
1 2
3 1
4
0 0
1 0
0 1
1 1

*/