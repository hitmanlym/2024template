#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
void solve() {
	int q;
	std::cin >> q;
	std::vector<int> a;
	int sum = 0;
	int s = 0;
	while (q --) {
		int t, v;
		std::cin >> t >> v;
		while (t --) {
			//sum -= a.back();
			s -= a.back() * a.size();
			s %= mod;
			a.pop_back();
		}
		a.push_back(v);
		//sum += v;
		s += v * a.size();
		s %= mod;

		//int ans = sum * a.size() - s;
		std::cout << (s + mod) % mod << '\n';
	}
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