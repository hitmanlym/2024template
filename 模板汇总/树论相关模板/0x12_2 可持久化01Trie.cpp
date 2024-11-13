#include<bits/stdc++.h>
using i64 = long long;

const int N = 6e5 + 10;
int rt[N], tot, s[N], n, m;
struct TireLL {
	int max_id;
	int c[2]; // 26
} t[N << 5];
void insert(int i, int k, int p, int q) {
	if (k < 0) {
		t[q].max_id = i;
		return ;
	}
	int v = s[i] >> k & 1;
	if (p) {
		t[q].c[v ^ 1] = t[p].c[v ^ 1];
	}
	t[q].c[v] = ++ tot;
	insert(i, k - 1, t[p].c[v], t[q].c[v]);
	t[q].max_id = std::max(t[t[q].c[0]].max_id, t[t[q].c[1]].max_id);
}
int query(int rt, int f, int l) {
	int p = rt;
	for (int i = 23; i >= 0; i --) {
		int v = f >> i & 1;
		if (t[t[p].c[v ^ 1]].max_id >= l) p = t[p].c[v ^ 1];
		else p = t[p].c[v];
	}
	return f ^ s[t[p].max_id];
}	
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> m;
	t[0].max_id = -1;
	rt[0] = ++ tot;
	insert(0, 23, 0, rt[0]);
	for (int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		s[i] = s[i - 1] ^ x;
		rt[i] = ++ tot;
		insert(i, 23, rt[i - 1], rt[i]);
	}

	char op;
	int l, r, x;
	while (m --) {
		std::cin >> op;
		if (op == 'A') {
			std::cin >> x;
			n ++;
			s[n] = s[n - 1] ^ x;
			rt[n] = ++ tot;
			insert(n, 23, rt[n - 1], rt[n]);
		} else {
			std::cin >> l >> r >> x;
			std::cout << query(rt[r - 1], s[n] ^ x, l - 1) << '\n'; // 异或掉
		}
	}
	return 0;
}