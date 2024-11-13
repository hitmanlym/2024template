#include<bits/stdc++.h>
using i64 = long long;

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

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	int max = 0;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		max = std::max(max, a[i]);
	}
	std::vector<int> num(max + 1);
	std::vector<i64> dp(max + 1);
	sieve(max);
	for (int i = 1; i <= n; i ++) {
		int t = a[i];
		for (int j = 1; j * j <= t; j ++) {
			if (t % j == 0) {
				num[j] ++;
				if (j * j != t) {
					num[t / j] ++;
				}
			}
		}
	}
	i64 ans = 0;
	for (int i = max; i >= 1; i --) {
		if (! num[i]) continue;
		dp[i] = 1ll * num[i] * i;
		for (int j = 0; j < primes.size(); j ++) {
			if (primes[j] * i > max) break;
			dp[i] = std::max(dp[i], dp[primes[j] * i] + 1ll * (num[i] - num[primes[j] * i]) * i);
		}
		ans = std::max(ans, dp[i]);
	}
	std::cout << ans << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}