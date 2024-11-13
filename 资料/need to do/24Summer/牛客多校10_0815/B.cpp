#include<bits/stdc++.h>
using i64 = long long;
void solve() { // 二叉树
	int n, m;
	struct node {
		std::string s;
		int l = -1, r = -1;
	};
	std::vector<node> op;
	std::cin >> n >> m;
	//std::map<std::string, int> mp;
	std::string aa;

	/*
	auto dfs = [&](auto self, int l, int r, int f) -> void {
		int mid = -1, res = 0;
		for (int i = l; i <= r; i ++) {
			if (aa[i] == '<') res ++;
			if (aa[i] == '>') res --;

			if (aa[i] == ',' && res == 0) {
				mid = i;
				break;
			}
		}
		std::string lson = "", rson = "";
		for (int i = l; i < mid; i ++) {
			lson += aa[i];
		}
		for (int i = mid + 1; i <= r; i ++) {
			rson += aa[i];
		}
		node ll, rr;
		ll.s = lson, rr.s = rson;
		op.push_back(ll);
		int lid = op.size() - 1;
		op.push_back(rr);
		int rid = op.size() - 1;
		op[f].l = lid;
		op[f].r = rid;
		// 300 * 5000


		if (aa[l] == 'p') {
			self(self, l + 5, mid - 2, lid);
		}
		if (aa[mid + 1] == 'p') {
			self(self, mid + 6, r - 1, rid);
		}
	};
	*/	
	std::vector<std::string> X(n + 1), Y(n + 1);


	for (int i = 1; i <= n; i ++) {
		std::cin >> X[i] >> Y[i];
	}
	while (m --) {
		std::string x;
		std::cin >> x;
		int l = 0;
		std::string tt = "";
		while (l < x.size() && x[l] != '.') {
			tt += x[l];
			l ++;
		}
		tt += ";";
		l ++;
		std::string rev;
		for (int i = 1; i <= n; i ++) {
			if (Y[i] == tt) {
				rev = X[i];
			}
		}
		int L = 0, R = rev.size() - 1;


		//std::cout << "?? " << L << ' ' << R << '\n';
		while (l < x.size()) {
			int sig = -1;
			if (x[l] == 'f') sig = 1;
			else sig = 2;
			while (l < x.size() && x[l] != '.') {
				l ++;
			}
			l ++;
			if (sig == 1) {
				L += 5;
				int res = 0;
				for (R = L; ; R ++) {
					if (rev[R] == '<') res ++;
					if (rev[R] == '>') res --;
					if (rev[R] == ',' && res == 0) {
						R --;
						break;
					}
				}
			}
			else {
				R --;
				int res = 0;
				for (L = R; ; L --) {
					if (rev[L] == '<') res ++;
					if (rev[L] == '>') res --;
					if (rev[L] == ',' && res == 0) {
						L ++;
						break;
					}
				}
			}

			//std::cout << "!! " << L << ' ' << R << '\n';
		} 
		for (int i = L; i <= R; i ++) {
			std::cout << rev[i];
		}
		std::cout << '\n';
	}
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
/*
1 1
pair<int,pair<int,pair<int,double>>> __op;
__op.second.second.second
*/