#include<bits/stdc++.h>
using i64 = long long;
struct DikaerBuild {
	int n, rt, tot;
	std::vector<int> a, st, ans;
	struct node{
		int lc, rc;
	};
	std::vector<node> tr;
	DikaerBuild() {}
	void init(int n, std::vector<int> b) {
		this -> n = n;
		a.assign(b.begin(), b.end());
		st.assign({});
		tr.assign(n + 1, {0, 0});
		ans.assign(n + 1, 0);
		rt = 0;
		tot = 0;
		build();
	}
	void build() {
		for (int i = 1; i <= n; i ++) {
			int last = 0;
			while (st.size() && a[st.back()] > a[i]) {
				last = st.back();
				st.pop_back();
			}
			if (st.size()) tr[st.back()].rc = i;
			else rt = i;

			tr[i].lc = last;
			st.push_back(i);
		}
	}
	void dfs(int u) {
		ans[u] = ++ tot;
		std::cout << u << ' ';
		if (tr[u].lc) dfs(tr[u].lc);
		if (tr[u].rc) dfs(tr[u].rc);
	}
};
// 给定排列a，生成任意区间最小值位置相同的字典序最小排列。 ans[it] 形式化的最小字典序
// new -  BST 的生成序列， 其序列生成的先序遍历即为所求。

// 笛卡尔树满足BST性质，其为权值随机的Treap, 权值满足下标为 w 。
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		//std::cin >> a[i];
		int x;
		std::cin >> x;
		a[x] = i;
	}
	DikaerBuild t;
	t.init(n, a);
	t.dfs(t.rt);/*
	for (int i = 1; i <= n; i ++) {
		std::cout << t.ans[i] << ' ';
	}*/
	std::cout << '\n';
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}