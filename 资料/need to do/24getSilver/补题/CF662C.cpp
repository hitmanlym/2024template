#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using Poly = std::vector<int>;

struct FWT {
    void FWTxor(Poly &a, bool rev) {
    	int n = a.size();
        for (int l = 2, m = 1; l <= n; l <<= 1, m <<= 1) {
            for (int j = 0; j < n; j += l) for (int i = 0; i < m; i++) {
                int x = a[i + j], y = a[i + j + m];
                if (!rev) {
                    a[i + j] = (x + y);
                    a[i + j + m] = (x - y);
                } else {
                    a[i + j] = 1LL * (x + y) / 2;
                    a[i + j + m] = 1LL * (x - y) / 2;
                }
            }
        }
    }
    Poly Xor(Poly a1, Poly a2) {
        int n = std::max(a1.size(), a2.size()), N = n;
        a1.resize(N), FWTxor(a1, false);
        a2.resize(N), FWTxor(a2, false);
        Poly A(N);
        for (int i = 0; i < N; i++) A[i] = 1LL * a1[i] * a2[i];
        FWTxor(A, true);
        return A;
    }
} fwt;
const int inf = 1e18;
void solve() { // n = 2 ^ m 个数.
   	int n, m;
   	std::cin >> n >> m;
   	int lim = 1 << n;
   	Poly g(m);
   	for (int i = 0; i < n; i ++) {
   		std::string s;
   		std::cin >> s;
   		for (int j = 0; j < m; j ++) {
   			if (s[j] == '1') g[j] |= (1 << i);
   		}
   	}
   	Poly a(lim), cnt(lim), b(lim);
   	for (int i = 0; i < m; i ++) {
   		a[g[i]] ++;
   	}
   	for (int i = 1; i < lim; i ++) {
   		cnt[i] = cnt[i >> 1] + (i & 1);
   	}
   	for (int i = 0; i < lim; i ++) {
   		b[i] = std::min(cnt[i], n - cnt[i]);
   	}
   	auto it = fwt.Xor(a, b);
   	int ans = inf;
   	for (int i = 0; i < lim; i ++) {
   		ans = std::min(ans, it[i]);
   	}
   	std::cout << ans << '\n';
}
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}
