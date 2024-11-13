#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
void solve() {
	int n;
	std::cin >> n;
	std::vector<std::array<int, 2> > a(n);
	for (int i = 0; i < n; i ++) {
		std::cin >> a[i][1] >> a[i][0];
	} 
	std::sort(a.begin(), a.end());

	std::priority_queue<pii, std::vector<pii>, std::less<pii> > q;
	int sum = 0;
	for (int i = 0; i < n; i ++) {
		sum += a[i][1];
		q.push({a[i][1], i});
		if (sum > a[i][0]) {
			auto it = q.top();
			q.pop();
			sum -= it[0];
		}
	}
	std::cout << q.size() << '\n';
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