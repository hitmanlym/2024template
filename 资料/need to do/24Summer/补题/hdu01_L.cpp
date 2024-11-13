#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
using i64 = long long;
const int mod = 998244353;
const int inf = 2e9;
int qmi(int a, int b = mod - 2) {
    if (a == 0) return 0;
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1ll * res * a % mod;
        }
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}
struct Comb {
    int n;
    std::vector<int> _fac, _invfac, _inv;
    //Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    void init(int m) {
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        _fac[0] = 1;
        _invfac[0] = 1;
        _inv[0] = 0;

        for (int i = n + 1; i <= m; i ++) {
            _fac[i] = 1ll * _fac[i - 1] * i % mod;
        }
        _invfac[m] = qmi(_fac[m], mod - 2);
        for (int i = m; i > n; i --) {
            _invfac[i - 1] = 1ll * _invfac[i] * i % mod;
            _inv[i] = 1ll * _invfac[i] * _fac[i - 1] % mod;
        }
        n = m;
    }
    int fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    int invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    int inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    int binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1ll * fac(n) * invfac(m) % mod * invfac(n - m) % mod;
    }
};
void solve() {
	
	int n;
	std::cin >> n;
	Comb comb;
	comb.init(n);
	std::vector<int> x, y;
	std::vector<std::array<int, 4> > op(n + 1); 
	for (int i = 1; i <= n; i ++) {
		int x1, y1, x2, y2;
		std::cin >> x1 >> y1 >> x2 >> y2;
		op[i] = {x1, y1,  x2, y2};
		x.push_back(x1);
		x.push_back(x2);
		y.push_back(y1);
		y.push_back(y2);
	}
	x.push_back(-inf);
	y.push_back(-inf);

	std::sort(x.begin(), x.end());
	x.erase(std::unique(x.begin(), x.end()), x.end());
	std::sort(y.begin(), y.end());
	y.erase(std::unique(y.begin(), y.end()), y.end());
	
	std::vector<std::vector<int> > z(x.size(), std::vector<int>(y.size()));
	for (int i = 1; i <= n; i ++) {
		int x1 = std::lower_bound(x.begin(), x.end(), op[i][0]) - x.begin();
		int x2 = std::lower_bound(x.begin(), x.end(), op[i][2]) - x.begin();
		int y1 = std::lower_bound(y.begin(), y.end(), op[i][1]) - y.begin();
		int y2 = std::lower_bound(y.begin(), y.end(), op[i][3]) - y.begin();

		z[x1][y1] ++;
		z[x2][y1] --;
		z[x1][y2] --;
		z[x2][y2] ++;
	}
	std::vector<int> f(n + 1);
	for (int i = 1; i < x.size(); i ++) {
		for (int j = 1; j < y.size(); j ++) {
			z[i][j] += z[i][j - 1];
		}
	}
	for (int i = 1; i < x.size() - 1; i ++) {
		for (int j = 1; j < y.size() - 1; j ++) {
			z[i][j] += z[i - 1][j];
			f[z[i][j]] = (f[z[i][j]] + 1ll * (x[i + 1] - x[i]) * (y[j + 1] - y[j]) % mod) % mod;
		}
	}
	i64 S = 0;
	for (int i = 1; i <= n; i ++) {
		S = (S + f[i]) % mod;
	}

	std::vector<int> ans(n + 1);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			ans[j] = (ans[j] - 1ll * comb.binom(n - i, j) * f[i] % mod + mod) % mod;
		}
	}
	for (int i = 1; i <= n; i ++) {
		ans[i] = (1ll * ans[i] * qmi(comb.binom(n, i)) % mod + S) % mod;
	}
	for (int i = 1; i <= n; i ++) {
		std::cout << ans[i] << '\n';
	}
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