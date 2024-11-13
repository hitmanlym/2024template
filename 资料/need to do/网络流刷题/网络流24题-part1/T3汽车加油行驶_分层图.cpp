#include<bits/stdc++.h>
using i64 = long long;

const int E = 2e6 + 10;
const int V = 2e5 + 10;
const int inf = 1e9;
int n, etot = 0, head[V], d[V];
bool vis[V];
struct edge {
	int v, nxt, w;
} e[E];
void addedge(int a, int b, int c, int x, int y, int z, int g) {
	int l = n * n * c + (a - 1) * n + b;
	int r = n * n * z + (x - 1) * n + y;
	e[etot] = {r, head[l], g}; head[l] = etot ++;
}
void solve() {
	int k, p, b, c;
	std::cin >> n >> k >> p >> b >> c;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			int x;
			std::cin >> x;
			if (! x) {
				for (int o = 0; o < k; o ++) {
					addedge(i, j, o, i, j, k, p + c);
				}
				for (int o = 1; o <= k; o ++) {
					if (i > 1) addedge(i, j, o, i - 1, j, o - 1, b);
					if (j > 1) addedge(i, j, o, i, j - 1, o - 1, b);
					if (i < n) addedge(i, j, o, i + 1, j, o - 1, 0);
					if (j < n) addedge(i, j, o, i, j + 1, o - 1, 0);
				}
			} else {
				for (int o = 0; o < k; o ++) {
					addedge(i, j, o, i ,j, k, p);
				}
				if (i > 1) addedge(i, j, k, i - 1, j, k - 1, b);
				if (j > 1) addedge(i, j, k, i, j - 1, k - 1, b);
				if (i < n) addedge(i, j, k, i + 1, j, k - 1, 0);
				if (j < n) addedge(i, j, k, i, j + 1, k - 1, 0);
			}
		}
	}
	for (int i = 0; i <= k; i ++) {
		addedge(n, n, i, 1, 1, k + 1, 0);
	}
	for (int i = 1; i <= n * n * (k + 1) + 1; i ++) {
		d[i] = inf;
	}
	int s = n * n * k + 1;
	std::queue<int> q;
	d[s] = 0;
	q.push(s);
	while (! q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (d[v] > d[u] + e[i].w) {
				d[v] = d[u] + e[i].w;
				if (! vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
	int ans = d[n * n * (k + 1) + 1];
	std::cout << ans << '\n';
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