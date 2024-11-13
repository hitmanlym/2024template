#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define i64 long long

const int N = 5e3 + 10, M = 61, mod = 1e9 + 7;
int a[N], m;
i64 f[N][M + 1][M + 1];
i64 dd[N];
i64 dfs(int len, bool limit, int d, int sum) {
	if (d < 0) d += m;
	while (sum >= m) sum -= m;
	// cut
	if (! len) return d == 0;
	if (! limit && f[len][d][sum] != -1) return f[len][d][sum];
	i64 res = 0;
	int end = limit ? a[len] : 9;
	for (int i = 0; i <= end; i ++) {
		res += dfs(len - 1, 
			limit && i == end, 
			(d + sum * i - i * dd[len - 1]) % m, 
			(sum + i));
		res %= mod;
	}
	if (! limit) f[len][d][sum] = res;
	return res % mod;
}
char L[N + 10], R[N + 10];
i64 dp(char *str) {
	int len = strlen(str);
	for (int i = 1; i <= len; i ++) {
		a[i] = str[len - i] - '0';
	}
	for (int i = 1; i <= len; i ++) {
		dd[i] = dd[i - 1] * 10 % m;
	}
	for (int i = 0; i <= len; i ++) {
		for (int j = 0; j <= m; j ++) {
			for (int k = 0; k <= m; k ++) {
				f[i][j][k] = -1;
			}
		}
	}
	return dfs(len, 1, 0, 0);
}
int read(){
    int red=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') f=-f;ch=getchar();}
    while(ch>='0'&&ch<='9') red=red*10+ch-48,ch=getchar();
    return red*f;
}
void solve() {
	int n = 1;
	n = read();
	dd[0] = 1;

	auto check = [&](char *s) -> bool {
		int x = 0, fx = 0, sum = 0;
		int n = strlen(s);
		for (int i = 0; i < n; i ++) {
			x = (x * 10 + s[i] - '0') % m;
			fx = (fx + sum * (s[i] - '0')) % m;
			sum = (sum + (s[i] - '0')) % m;
		}
		return x == fx;
	};

	for (int i = 1; i <= n; i ++) {
		
		scanf("%s", L);
		scanf("%s", R);
		//
		m = read();
		int fix = 0;
		// check(l) -> fix + 1
		if (check(L)) {
			fix = 1;
		}
		std::cout << ((dp(R) - dp(L) + fix) % mod + mod) % mod << '\n';
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	//std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}