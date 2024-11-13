#include<bits/stdc++.h>
#pragma gcc optimize("O2")
#pragma g++ optimize("O2")
using i64 = long long;
const int mod = 1e9 + 7;
struct Matrix {
	i64 M[5][5], n = 4;
	Matrix() {memset(M, 0, sizeof(M));}
	Matrix(int v) {
		M[1][2] = v;
		M[1][3] = M[1][4] = 1ll * v * v % mod;
		M[2][3] = M[2][4] = 2 * v % mod;
		M[3][4] = 1;
		M[1][1] = M[2][2] = M[3][3] = M[4][4] = 1;
		M[2][1] = M[3][1] = M[3][2] = M[4][1] = M[4][2] = M[4][3] = 0;
	}
	void init() {
		for (int i = 1; i <= 4; i ++) {
			for (int j = 1; j <= 4; j ++) {
				M[i][j] = ((i == j) ? 1 : 0);
			}
		}
	}
	Matrix friend operator * (const Matrix &a, const Matrix &b) {
		Matrix ans;
		int n = a.n;
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				for (int k = 1; k <= n; k ++) {
					ans.M[i][j] = (ans.M[i][j] + a.M[i][k] * b.M[k][j]) % mod;
				}
			}
		}
		return ans;
	}
};
const int N = 1e5 + 10;
struct Node {
	int val[5];
	Node() { memset(val, 0, sizeof val); }
	Node(i64 x) { val[1] = 1, val[2] = x, val[3] = val[4] = x * x % mod; }
	Node operator + (Node &b)
	{
		Node res;
		for (int i = 1; i <= 4; ++i)
			res.val[i] = (val[i] + b.val[i]) % mod;
		return res;
	}
	Node operator * (Matrix &b)
	{
		int res[5] = { 0 };
		for (int i = 1; i <= 4; ++i)
			for (int j = 1; j <= 4; ++j)
				res[j] = (res[j] + 1ll * val[i] * b.M[i][j]) % mod;
		for (int i = 1; i <= 4; ++i)
			val[i] = res[i];
		return *this;
	}
};
int a[N];
Matrix add[N * 4];
Node tr[N * 4];
int n;
void pushup(int u) {
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void pushdown(int u) {
    tr[u << 1] = tr[u << 1] * add[u];
    tr[u << 1 | 1] = tr[u << 1 | 1] * add[u];
    add[u << 1] = add[u << 1] * add[u];
	add[u << 1 | 1] = add[u << 1 | 1] * add[u];
	add[u].init();
}
void build(int u, int l, int r) {
    add[u].init();
    if (l == r) {
        tr[u] = Node(a[l]);
        return ;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
void addd(int u, int L, int R, int l, int r, int v) {
    if ((L >= l && R <= r) || L > r || R < l) {
    	Matrix tmp((L >= l && R <= r) ? v : 0);
    	tr[u] = tr[u] * tmp;
        add[u] = add[u] * tmp;
        return ;
    }
    pushdown(u);
    int mid = L + R >> 1;
    addd(u << 1, L, mid, l, r, v);
    addd(u << 1 | 1, mid + 1, R, l, r, v);
    pushup(u);
}

int query(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].val[4];
    }
    pushdown(u);
    int res = 0;
    int mid = L + R >> 1;
    if (l <= mid) res = (res + query(u << 1, L, mid, l, r)) % mod;
    if (mid < r) res = (res + query(u << 1 | 1, mid + 1, R, l, r)) % mod;
    return res;
}
void addd(int l, int r, int v) {
    addd(1, 1, n, l, r, v);
}
int query(int l, int r) {
    return query(1, 1, n, l, r); // D, history sum.
}

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


int main() {
	n = read();
	int m = read();
	int q = read();
	for (int i = 1; i <= n; i ++) {
		a[i] = (read() + mod) % mod;
	}
	build(1, 1, n);

	std::vector<std::array<int, 3> > op(m + 1);
	for (int i = 1; i <= m; i ++) {
		op[i][0] = read();
		op[i][1] = read();
		op[i][2] = (read() + mod) % mod;
	}
	std::vector<std::vector<std::array<int, 4> > > p(m + 1);
	std::vector<int> ans(q + 1);
	for (int i = 1; i <= q; i ++) {
		int l = read();
		int r = read();
		int x = read();
		int y = read();
		if (x - 1 >= 0) p[x - 1].push_back({-1, i, l, r});
		p[y].push_back({1, i, l, r});
	}

	for (int i = 0; i <= m; i ++) {
		if (i) {
			int l = op[i][0], r = op[i][1], v = op[i][2];
			addd(l, r, v);
		}
		for (auto it : p[i]) {
			int sig = it[0], j = it[1], l = it[2], r = it[3];
			int val = query(l, r);
			//std::cout << ans[j] << ' ' << val << ' ' << l << ' ' << r << ' ' << "???\n";
			ans[j] = (ans[j] + val * sig) % mod;
		}
		//std::cout << "TEST : " << t.query(4, 4) << '\n';
	}
	for (int i = 1; i <= q; i ++) {
		ans[i] = (ans[i] + mod) % mod;
		std::cout << ans[i] << '\n';
	}
	return 0;
}
/*
4 1 1
2 3 2 2
1 1 6
4 4 0 1

*/