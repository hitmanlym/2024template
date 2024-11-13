#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::pair<int, int>> events;
    i64 suma = 0, sumb = 0;
    
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;
        suma += r - l;
        
        if (l == r) {
            events.emplace_back(l, 2);
        } else {
            events.emplace_back(l, 0);
            events.emplace_back(r, 1);
        }
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        sumb += r - l;
        
        if (l == r) {
            events.emplace_back(l, 5);
        } else {
            events.emplace_back(l, 3);
            events.emplace_back(r, 4);
        }
    }
    
    i64 cnta = 0, cntb = 0;
    i64 ka = 0, kb = 0, sa = 0, sb = 0;
    i64 last = 0;
    
    double ans = 0;
    
    std::sort(events.begin(), events.end());
    for (auto [x, i] : events) {
        std::array<double, 3> f{};
        f[0] = 1;
        
        if (suma == 0) {
            f[0] *= 1. * cnta / n;
            f[1] *= 1. * cnta / n;
        } else {
            f[2] += 1. * f[1] * ka / suma;
            f[1] *= 1. * sa / suma;
            f[1] += 1. * f[0] * ka / suma;
            f[0] *= 1. * sa / suma;
        }
        if (sumb == 0) {
            f[0] *= 1. * (m - cntb) / m;
            f[1] *= 1. * (m - cntb) / m;
        } else {
            f[2] += 1. * f[1] * -kb / sumb;
            f[1] *= 1. * (sumb - sb) / sumb;
            f[1] += 1. * f[0] * -kb / sumb;
            f[0] *= 1. * (sumb - sb) / sumb;
        }
        
        ans += 1. * f[0] * (x - last);
        ans += 1. * f[1] * (1. * x * x - 1. * last * last) / 2;
        ans += 1. * f[2] * (1. * x * x * x - 1. * last * last * last) / 3;
        
        f = {1.};
        
        if (sumb == 0) {
            f[0] *= 1. * cntb / m;
            f[1] *= 1. * cntb / m;
        } else {
            f[2] += 1. * f[1] * kb / sumb;
            f[1] *= 1. * sb / sumb;
            f[1] += 1. * f[0] * kb / sumb;
            f[0] *= 1. * sb / sumb;
        }
        if (suma == 0) {
            f[0] *= 1. * (n - cnta) / n;
            f[1] *= 1. * (n - cnta) / n;
        } else {
            f[2] += 1. * f[1] * -ka / suma;
            f[1] *= 1. * (suma - sa) / suma;
            f[1] += 1. * f[0] * -ka / suma;
            f[0] *= 1. * (suma - sa) / suma;
        }
        
        ans += 1. * f[0] * (x - last);
        ans += 1. * f[1] * (1. * x * x - 1. * last * last) / 2;
        ans += 1. * f[2] * (1. * x * x * x - 1. * last * last * last) / 3;
        
        if (i == 0) {
            sa -= x;
            ka++;
        } else if (i == 1) {
            sa += x;
            ka--;
        } else if (i == 2) {
            cnta++;
        } else if (i == 3) {
            sb -= x;
            kb++;
        } else if (i == 4) {
            sb += x;
            kb--;
        } else {
            cntb++;
        }
        last = x;
    }
    
    std::cout << std::fixed << std::setprecision(10);
    std::cout << ans << "\n";
    
    return 0;
}
