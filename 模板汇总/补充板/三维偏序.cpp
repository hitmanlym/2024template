#include<bits/stdc++.h>
using i64 = long long;
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
struct node {
	int x, y, z;
	int ans, w;
};
bool cmp1(node u, node v) {
	return u.x < v.x || 
		u.x == v.x && u.y < v.y || 
		u.x == v.x && u.y == v.y && u.z < v.z;
}
bool cmp2(node u, node v) {
	return u.y < v.y || 
		u.y == v.y && u.z < v.z;
}
struct CDQ {
	int n;
	Fenwick t;
	std::vector<node> a;
	std::vector<int> cnt;
	void init(int n, std::vector<int> x, std::vector<int> y, std::vector<int> z) {
		t.init(3 * n);
		std::vector<node> b(n + 1);
		cnt.assign(n + 1, 0);
		a.resize(1);
		// 去重
		std::vector<int> v;
		for (auto it : x) { v.push_back(it); }
		for (auto it : y) { v.push_back(it); }
		for (auto it : z) { v.push_back(it); }
		std::sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
		for (int i = 1; i <= n; i ++) {
			int nx = std::lower_bound(v.begin(), v.end(), x[i]) - v.begin() + 1;
			int ny = std::lower_bound(v.begin(), v.end(), y[i]) - v.begin() + 1;
			int nz = std::lower_bound(v.begin(), v.end(), z[i]) - v.begin() + 1;
			b[i] = {nx, ny, nz, 0, 0};
		}
		std::sort(b.begin() + 1, b.end(), cmp1);
		for (int i = 1, cnt = 0; i <= n; i ++) {
			cnt ++;
			if (i == n || b[i].x != b[i + 1].x ||
						  b[i].y != b[i + 1].y || 
						  b[i].z != b[i + 1].z) {
				node it = b[i];
				it.w = cnt; // repeat times
				cnt = 0;
				a.push_back(it);
			}
		}
		this -> n = a.size() - 1;
	}
	void cdq(int l, int r) {
		if (l == r) return ;
		int mid = l + r >> 1;
		cdq(l, mid);
		cdq(mid + 1, r);
		std::sort(a.begin() + l, a.begin() + mid + 1, cmp2);
		std::sort(a.begin() + mid + 1, a.begin() + r + 1, cmp2);
		int i = l, j = mid + 1;
		while (j <= r) {
			while (i <= mid && a[i].y <= a[j].y) {
				t.add(a[i].z, a[i].w);
				i ++;
			}
			a[j].ans += t.sum(a[j].z);
			j ++;
		}
		for (int k = l; k < i; k ++) {
			t.add(a[k].z, -a[k].w);
		}
	}
	std::vector<int> work() {
		cdq(1, n);
		for (int i = 1; i <= n; i ++) {
			cnt[a[i].ans + a[i].w - 1] += a[i].w;
		}
		return cnt;
	}
};
void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n + 1), b(n + 1), c(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i] >> b[i] >> c[i];
	}
	CDQ p;
	p.init(n, a, b, c);
	auto d = p.work();
	for (int i = 0; i < n; i ++) {
		std::cout << d[i] << '\n';
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