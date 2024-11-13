#include<bits/stdc++.h>
using i64 = long long;
#define int i64
using pii = std::array<int, 2>;
const int inf = 1e18;
void solve() {
	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<std::vector<pii> > e(n + 1);
	std::vector<std::map<int, int> > mp(n + 1);
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		mp[u][v] = mp[v][u] = w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	std::vector<bool> vis(n + 1, 1);
	std::vector<int> dis(n + 1, inf);
	int B = std::sqrt(n + 1);
	while (q --) {
		int k;
		std::cin >> k;
		if (k > B) {
			std::vector<int> a(k + 1);
			for (int i = 1; i <= k; i ++) {
				std::cin >> a[i];
				vis[a[i]] = 0;
				dis[a[i]] = inf;
			}
			int s = a[1];
			dis[s] = 0;
			//std::cout << "CRAZY " << dis[2] << '\n';
			std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
			q.push({0, s});
			
			int cnt = 0, sum = 0;
			while (! q.empty() && cnt < k) {
				auto it = q.top();
				int u = it[1], d = it[0];
				q.pop();
				if (vis[u]) continue;
				cnt ++;
				vis[u] = 1;
				sum += d;
				//std::cout << "? " << u << '\n';
				for (auto op : e[u]) {
					int v = op[0], w = op[1];
					//std::cout << "## " << v << ' ' << w << " " << dis[v] << '\n';
					if (dis[v] > w) {
						dis[v] = w;
						q.push({dis[v], v});
						//std::cout << "!!! " << v << ' ' << dis[v] << '\n';
					}
				}
			}
			if (cnt < k) {
				std::cout << -1 << '\n';
			} else {
				std::cout << sum << '\n';
			}
			for (int i = 1; i <= k; i ++) {
				vis[a[i]] = 1;
			}
		} else {
			std::vector<int> a(k + 1);
			for (int i = 1; i <= k; i ++) {
				std::cin >> a[i];
				dis[a[i]] = inf;
				vis[a[i]] = 0;
			}
			int sum = 0, cnt = 1;
			int s = a[1];
			dis[s] = 0;
			for (int i = 1; i <= k; i ++) {
				if (mp[s].count(a[i]))
					dis[a[i]] = std::min(dis[a[i]], mp[s][a[i]]);
			}
			for (int i = 1; i < k; i ++) {
				int min = inf;
				vis[s] = 1;
				for (int j = 1; j <= k; j ++) {
					if (! vis[a[j]] && min > dis[a[j]]) {
						min = dis[a[j]];
						s = a[j];
					}
				}
				if (min == inf) {
					break;
				}
				cnt ++;
				sum += min;
				for (int j = 1; j <= k; j ++) {
					if (mp[s].count(a[j]))
						dis[a[j]] = std::min(dis[a[j]], mp[s][a[j]]);
				}
			}

			if (cnt < k) {
				std::cout << -1 << '\n';
			} else {
				std::cout << sum << '\n';
			}
			for (int i = 1; i <= k; i ++) {
				vis[a[i]] = 1;
			}
		}
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