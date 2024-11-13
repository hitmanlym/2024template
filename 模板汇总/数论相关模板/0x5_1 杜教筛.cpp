#include<bits/stdc++.h>
using i64 = long long;
const int N = 5e6 + 10;

std::vector<int> minp, primes, mu;
std::vector<i64> phi;
std::unordered_map<int, int> ans_mu;
std::unordered_map<int, i64> ans_phi;

void sieve(int n) {
    minp.assign(n + 1, 0);
    phi.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    primes.clear();
    
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }

            minp[i * p] = p;
            if (p == minp[i]) {
            	phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
            mu[i * p] -= mu[i];
        }
    }
    for (int i = 1; i <= n; i ++) {
    	mu[i] += mu[i - 1];
    	phi[i] += phi[i - 1];
    }
}
struct Du{
	i64 get_phi(i64 x) {
	    if (x <= N) return phi[x];
	    if (ans_phi[x]) return ans_phi[x];
	    i64 ans = ((1ll + x) * x) / 2ll;
	    for (i64 l = 2, r; l <= x; l = r + 1) {//其实这里可能会爆int
	        r = x / (x / l);
	        ans -= 1ll * (r - l + 1) * get_phi(x / l);
	    }
	    return ans_phi[x] = ans;
	}
	int get_mu(int x) {
	    if (x <= N) return mu[x];
	    if (ans_mu[x]) return ans_mu[x];
	    int ans = 1;
	    for(i64 l = 2, r; l <= x; l = r + 1) {
	        r = x / (x / l);
	        ans -= (r - l + 1) * get_mu(x / l);
	    }
	    return ans_mu[x] = ans;
	}
} tr;
void solve() {
	int n;
	std::cin >> n;
	i64 ans1 = tr.get_phi(n), ans2 = tr.get_mu(n);
	std::cout << ans1 << ' ' << ans2 << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	sieve(N);
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}