# 44H

通过一个手机号码找到另一个手机号码：

$S:15616154$

$T:x[x + 5 >> 1]...$

在取整时有两种情况，求最终能够得到多少其他电话号码。

```c++
void solve() {
	std::string s;
	std::cin >> s;
	int n = s.size();
	std::vector<int> v(n + 1);
	for (int i = 0; i < n; i ++) {
		v[i + 1] = s[i] - '0';
	}
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(10, 0));
	for (int i = 0; i < 10; i ++) {
		dp[1][i] = 1;
	}
	for (int i = 2; i <= n; i ++) {
		for (int j = 0; j < 10; j ++) {
			int a = j * 2 - v[i], b = a - 1, c = a + 1;
			if (a >= 0 && a < 10) dp[i][j] += dp[i - 1][a];
			if (b >= 0 && b < 10) dp[i][j] += dp[i - 1][b];
			if (c >= 0 && c < 10) dp[i][j] += dp[i - 1][c];
		}
	}
	int ans = -1;
	// !!! check if itself !!!
	for (int i = 2; i <= n; i ++) {
		if (std::abs(v[i] - v[i - 1] > 1)) {
			ans = 0;
		}
	}
	for (int i = 0; i < 10; i ++) {
		ans += dp[n][i];
	}
	std::cout << ans << '\n';
}
```

# 163A

字符串$s,t$，要求从$s$中选不同子串$x$，从$t$中选不同子序列$y$，求总共多少种组合使$x == y$。

> 考虑以$s_i$结尾的子串，以$t_j$结尾的子序列。

```c++
void solve() {
	std::string s, t;
	std::cin >> s >> t;
	int ls = s.size(), lt = t.size();
	// dp[i][j] s_i, t_j.
	std::vector<std::vector<int> > dp(ls + 1, std::vector<int>(lt + 1));
	for (int i = 0; i < ls; i ++) {
		for (int j = 0; j < lt; j ++) {
			dp[i + 1][j + 1] = (
				dp[i + 1][j] + (s[i] == t[j]) * (dp[i][j] + 1)
			) % mod;
		}
	}
	int ans = 0;
	for (int i = 1; i <= ls; i ++) {
		ans = (ans + dp[i][lt]) % mod;
	}
	std::cout << ans << '\n';
}
```

# 627A

$a + b = s;a ˆ b = x$，求有序对$(a, b)$个数。

> $(a + b) = (a \& b) * 2 + (a ˆ b)$.

```c++
void solve() {
	int s, x;
	std::cin >> s >> x;
	int a = (s - x) >> 1, cnt = 0, ans = 0;
	if ((s - x) & 1 || a & x || x > s) ans = 0;
	else {
		for (; x; cnt += x % 2, x >>= 1);	// 0/1
		ans = (1ll << cnt) - (a ? 0 : 2); 	// positive!
	}
	std::cout << ans << '\n';
}
```

