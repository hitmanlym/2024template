#include<bits/stdc++.h>
using i64 = long long;
const int N = 2e4;
struct Fenwick {
    int n;
    std::vector<int> a;

    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.resize(n + 1);
        a.assign(n + 1, 0);
    }
    void add(int x, int v) {
        for (; x <= n; x += x & -x) {
            a[x] += v;
        }
    }
    void add(int x, int y, int v) {
        add(x, v), add(y + 1, -v);
    }
    int sum(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans += a[x];
        }
        return ans;
    }
    int rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    int kth(int k) {   // kth value
        int ans = 0;
        for (int i = std::__lg(n); i >= 0; i--) {
            int val = ans + (1 << i);
            if (val < n && a[val] < k) {
                k -= a[val];
                ans = val;
            }
        }
        return ans + 1;
    }
};
void solve() {
	int n; 
	std::cin >> n;
	std::vector<std::vector<std::array<int, 2 > > > e(n + 1);
	for (int i = 1; i < n; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	} 
	int k;
	std::cin >> k;
	int ans = 0;
	Fenwick t(k);

	std::vector<int> siz(n + 1), maxp(n + 1); // son.max
	int rt, sum = n;
	maxp[rt = 0] = n;
	std::vector<bool> vis(n + 1);
	int num0 = 0;
	auto getRoot = [&](auto self, int u, int p) -> void {
		siz[u] = 1;
		maxp[u] = 0;
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == p || vis[v]) continue;
			self(self, v, u);
			siz[u] += siz[v];
			maxp[u] = std::max(maxp[u], siz[v]);
		}
		maxp[u] = std::max(maxp[u], sum - siz[u]);
		if (maxp[u] < maxp[rt]) rt = u;
	};
	std::vector<int> dis(n + 1);
	std::vector<int> qdis(n + 1), qremove(n + 1);
	auto getDis = [&](auto self, int u, int p) -> void {
		qdis[++ qdis[0]] = dis[u];
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (v == p || vis[v]) continue;
			dis[v] = dis[u] + w;
			self(self, v, u);
		}
	};
	auto calc = [&](int u) -> void {
		qremove[0] = 0;
		int p = 0;
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (vis[v]) continue;
			dis[v] = w;
			qdis[0] = 0;
			getDis(getDis, v, u);
			for (int i = 1; i <= qdis[0]; i ++) {
				if (qdis[i] <= k) {
					ans += t.rangeSum(1, k - qdis[i]) + num0;
				}
			}
			for (int i = 1; i <= qdis[0]; i ++) { // out of last loop ! will affect
				if (qdis[i] <= k && qdis[i] > 0) {
					t.add(qdis[i], 1);
					qremove[++ qremove[0]] = qdis[i];
				}
				if (qdis[i] == 0) {
					num0 ++;
				}
			}
		}
		for (int i = 1; i <= qremove[0]; i ++) {
			t.add(qremove[i], -1);
		}
	};
	auto dfz = [&](auto self, int u) -> void {
		vis[u] = 1;
		num0 = 1;
		calc(u);
		for (auto it : e[u]) {
			int v = it[0], w = it[1];
			if (vis[v]) continue;
			sum = siz[v];
			maxp[rt = 0] = siz[v];
			getRoot(getRoot, v, 0);
			self(self, rt);        // !!! rt
		}
	};
	getRoot(getRoot, 1, 0);
	dfz(dfz, rt);
	
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