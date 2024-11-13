#include <bits/stdc++.h>

using namespace std;

const int N = 5005, M = 1e6 + 5, S = 1000, P = 998244353;

int _a[M], _b[M], _c[M];
int v[M], p[M], r;
int f[S + 1][S + 1];
int a[N], b[N];

void Init()
{
	_a[1] = _b[1] = _c[1] = 1;
	for (int i = 2; i <= M - 5; ++i) {
		if (!v[i]) {
			p[++r] = i;
			_a[i] = _b[i] = 1, _c[i] = i; 
		}
		int tp;
		for (int j = 1; j <= r && (tp = i * p[j]) <= M - 5; ++j) {
			v[tp] = 1;
			_a[tp] = _a[i] * p[j];
			_b[tp] = _b[i];
			_c[tp] = _c[i];
			if (_a[tp] > _b[tp]) {
				swap(_a[tp], _b[tp]);
				if (_b[tp] > _c[tp]) {
					swap(_b[tp], _c[tp]);
				}
			}
			if (!(i % p[j])) {
				break;
			}
		}
	}
	
	for (int i = 1; i <= S; ++i) {
		f[0][i] = f[i][0] = i;
		for (int j = 1; j <= S; ++j) {
			f[i][j] = f[j % i][i];
		}
	}
	return;
}

int gcd(int x, int y)
{
	int A = 1, tp = f[_a[x]][y % _a[x]];
	A *= tp;
	y /= tp;
	tp = f[_b[x]][y % _b[x]];
	A *= tp;
	y /= tp;
	tp = (v[_c[x]] ? f[_c[x]][y % _c[x]] : (y % _c[x] ? 1 : _c[x]));
	A *= tp;
	y /= tp;
	return A;
}

signed main()
{
	Init();
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &b[i]);
	}
	for (int i = 1; i <= n; ++i) {
		int tp = 1, A = 0;
		for (int j = 1; j <= n; ++j) {
			tp = 1ll * tp * i % P;
			A = (A + 1ll * tp * gcd(a[i], b[j])) % P;
		}
		printf("%d\n", A);
	}
	return 0;
}