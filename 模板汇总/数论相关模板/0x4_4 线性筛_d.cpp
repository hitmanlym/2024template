#include<bits/stdc++.h>
using i64 = long long;

std::vector<int> minp, primes, d, num;
void sieve(int n) {
    minp.assign(n + 1, 0);
    d.assign(n + 1, 0);
    num.assign(n + 1, 0);
    primes.clear();
    
    d[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            d[i] = 2;
            num[i] = 1;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                num[i * p] = num[i] + 1;
                d[i * p] = d[i] / num[i * p] * (num[i * p] + 1);
                break;
            }
            num[i * p] = 1;
            d[i * p] = d[i] * 2;
        }
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