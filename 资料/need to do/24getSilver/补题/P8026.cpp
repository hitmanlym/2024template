#include<bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
std::mt19937_64 rng(std::random_device{}()); // 好像 _64 更快
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void solve() {
	int d, n, m;
	// std::cin >> d >> n >> m;
	d = read();
	n = read();
	m = read();
	std::vector<u64> val(d + 1), ha(n + 1);
	for (int i = 1; i <= d; i ++) {
		val[i] = rng();
	}
	std::vector<std::vector<int> > rt(d + 1, std::vector<int>(n + 1));
	std::vector<std::vector<std::vector<int> > > have(d + 1, std::vector<std::vector<int> >(n + 1));
	std::unordered_map<u64, int> cnt;
	i64 ans = 0;
	auto del = [&](u64 x) {
		cnt[x] --;
		if (cnt[x] == 0) {
			cnt.erase(x);
		}
		ans -= 2ll * cnt[x] + 1;
	};
	auto add = [&](u64 x) {
		ans += 2ll * cnt[x] + 1;
		cnt[x] ++;
	};
	for (int i = 1; i <= d; i ++) {
		for (int j = 1; j <= n; j ++) {
			rt[i][j] = j;
			have[i][j].push_back(j);
			ha[j] ^= 1ull * val[i] * j;
		}
	}
	for (int i = 1; i <= n; i ++) {
		add(ha[i]);
	}
	while (m --) {
		int u, v, k;
		// std::cin >> u >> v >> k;
		u = read();
		v = read();
		k = read();
		u = rt[k][u], v = rt[k][v];
		if (u == v) {
			std::cout << ans << '\n';
			continue;
		}
		if (have[k][u].size() < have[k][v].size()) {
			std::swap(u, v);
		}
		for (auto w : have[k][v]) {
			have[k][u].push_back(w);
			rt[k][w] = u;
			del(ha[w]);
			ha[w] ^= 1ull * val[k] * v;
			ha[w] ^= 1ull * val[k] * u;
			add(ha[w]);
		}
		std::cout << ans << '\n';
	}
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