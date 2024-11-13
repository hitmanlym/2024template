#include<bits/stdc++.h>
using i64 = long long;

void solve() {
    std::vector<int> a(3), b, c, op;
    for (int i = 1; i <= 3; i ++) {
        a[i - 1] = i;
    }
    i64 sum = 0;
    do {
        b = a;
        while (true) {
            op.clear();
            c.assign(b.size(), 0);
            for (int i = 0; i < b.size(); i ++) {
                if (i > 0 && std::abs(b[i] - b[i - 1]) == 1 
                    || i + 1 < b.size() && std::abs(b[i] - b[i + 1]) == 1) {
                    c[i] = 1;
                }
            }
            for (int i = 0; i < b.size(); i ++) {
                if (c[i] == 0) op.push_back(b[i]);
            }
            if (op.size() == b.size()) break;
            b = op;
        }
        std::cout << b.size() << '\n';
        sum += b.size();
    } while (std::next_permutation(a.begin(), a.end()));

    i64 total = 1;
    for (int i = 1; i <= 3; i ++) {
        total *= i;
    }
    int gcd = std::__gcd(sum, total);
    std::cout << sum << ' ' << total << '\n';
    std::cout << sum / gcd << " / " << total / gcd << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}