#include<bits/stdc++.h>
using i64 = long long;

std::vector<int> minp, primes, mu, sum_mu;
void sieve(int n) {
    minp.assign(n + 1, 0);
    sum_mu.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    primes.clear();
    
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            mu[i] = -1;
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
            mu[i * p] -= mu[i];
        }
    }
    for (int i = 1; i <= n; i ++) {
    	sum_mu[i] = sum_mu[i - 1] + mu[i];
    }
}

void solve() {
	int n, q;
	std::cin >> n >> q;
	sieve(n);
	while (q --) {
		int k;
		std::cin >> k;
		std::cout << primes[k - 1] << '\n';
	}
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