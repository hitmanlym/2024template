#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
const int N = 2e5 + 5;
std::vector<int> minp, primes;
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}
int n, k;
int a[N];
bool b[N];
using pii = std::array<int, 2>;
std::set<pii> st;
bool valid(int i, int x) {
    for (auto it : st) {
        int lsum = it[0], id = it[1];
        if (a[i] - lsum < x) return 0;
        if (b[i - id]) return 1;
    }
    return 0;
}
bool check(int x) {
    int mx = 0;
    st.clear();
    for (int i = 1; i <= n; i ++) {
        if (valid(i, x)) {
            st.clear();
            mx ++;
        } else {
            st.insert({a[i - 1], i - 1});
        }
        if (mx == k) break;
    }
    return mx == k;
}
void solve() {
    std::cin >> n >> k;
    int l = 0, r = 0, ans;
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
        if (a[i] > 0) r += a[i];
        else l += a[i];
        a[i] += a[i - 1];
    }
    if (n < 2 * k) {
        std::cout << "impossible\n";
        return ;
    }
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << ans << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    sieve(N);
    for (auto p : primes) {
        b[p] = 1;
    }
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}