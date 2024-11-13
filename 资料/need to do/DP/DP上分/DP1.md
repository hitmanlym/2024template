# T1 (466C)

$\sum_{k = 1}^{i - 1}{a_k} = \sum_{k = i}^{j}{a_k} = \sum_{k = j + 1}^{n}{a_k}$          $(2 \le i \le j \le n- 1)$

```c++
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> v(n);
	int sum = 0;
	for (int i = 0; i < n; i ++) {
		std::cin >> v[i];
		sum += v[i];
	}
	if (sum % 3 != 0) {
		std::cout << 0 << '\n';
		return ;
	}
	sum /= 3;
	int ans = 0, cnt = 0, l = 0;
	for (int i = 0; i < n - 1; i ++) {
		l += v[i];
		if (l == sum * 2) ans += cnt;	//后半段累加
		if (l == sum) cnt ++;			//前半段个数
	}
	std::cout << ans << '\n';
}
```

# T2 (474D)

$01$序列，其中$1$限制必须为连续$k$的倍数，求长度在$l \le length \le r$的方案数

```c++
void solve() {
	int t, k;
	std::cin >> t >> k;
	std::vector<int> s(M), h(M);
	h[0] = 1;
	for (int i = 1; i < M; i ++) {
		h[i] = h[i - 1];					//加A
		if (i - k >= 0) h[i] += h[i - k];	//加B（k个一起加）
		s[i] = s[i - 1] + h[i];
		h[i] %= mod;
		s[i] %= mod;						//前缀和
	}
	std::cout << '\n';
	while (t --) {
		int l, r;
		std::cin >> l >> r;
		std::cout << (s[r] - s[l - 1] + mod) % mod << '\n';
	}
}
```

# T3 (126B)

字符串 $S$，找满足为以下条件的最长的子串：

- 前缀
- 后缀
- 非前缀也非后缀

$fixprefixsuffix$ $:$ $fix$ 

```c++
void solve() {
	std::string s;
	std::cin >> s;

	int n = s.size();
	s = " " + s;

	std::vector<int> p(n + 1);
	int j = 0;
	p[1] = 0;
	for (int i = 2; i <= n; i ++) {						//kmp
		while (j > 0 && s[i] != s[j + 1]) j = p[j];
		if (s[i] == s[j + 1]) j ++;
		p[i] = j;
	}
	int ans = 0;
	for (int i = 1; i < n; i ++) {
		if (p[i] == p[n] || p[i] == p[p[n]]) ans = std::max(ans, p[i]);	//前后缀长度
		std::cout << p[i] << ' ' << p[n] << '\n';
	}
	if (ans == 0) {
		std::cout << "Just a legend\n";
	} else {
		for (int i = 1; i <= ans; i ++) {
			std::cout << s[i];
		}
		std::cout << '\n';
	}
}
```

# T4 (118D)

$01$序列，其中有$n_1$个$0$，$n_2$个$1$，限制：最长连续$0$的长度不超过$k_1$，最长连续$1$的长度不超过$k_2$。

```c++
void solve() {
	int n, m, x, y;
	std::cin >> n >> m >> x >> y;
	int dp[M][M][11][2];
	memset(dp, 0, sizeof dp);
	dp[1][0][1][0] = dp[0][1][1][1] = 1;
	int ans = 0;
	for (int i = 0; i <= n; i ++) {					// 用i个0，j个1，当前最后连续k个0/1
		for (int j = 0; j <= m; j ++) {
			if (i > 0) {
				for (int k = 2; k <= x; k ++) {
					dp[i][j][k][0] = dp[i - 1][j][k - 1][0];
				}
				for (int k = 1; k <= y; k ++) {
					dp[i][j][1][0] += dp[i - 1][j][k][1];
					dp[i][j][1][0] %= mod;
				}
			}
			if (j > 0) {
				for (int k = 2; k <= y; k ++) {
					dp[i][j][k][1] = dp[i][j - 1][k - 1][1];
				}
				for (int k = 1; k <= x; k ++) {
					dp[i][j][1][1] += dp[i][j - 1][k][0];
					dp[i][j][1][1] %= mod;
				}
			}
		}
	}
	for (int i = 1; i <= x; i ++) ans = (ans + dp[n][m][i][0]) % mod;
	for (int i = 1; i <= y; i ++) ans = (ans + dp[n][m][i][1]) % mod;
	std::cout << ans << '\n';
}
```