# T1 (467C)

$sec：$$[l_1, r_1], [l_2, r_2], ..., [l_k, r_k] \quad (1 \le l_1 \le r_1 \le l_2 \le r_2 ... \le l_k \le r_k \le n;r_i - l_i + 1 = m)$.

$maxvalue :$ $\sum_{i = 1}^{k}\sum_{j = l_i}^{r_i}{a_j}$

```c++
void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	// dp[i][j] --i, j sec
	std::vector<int > v(n + 1), s(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
		s[i] = s[i - 1] + v[i];
	}
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(k + 1));
	for (int i = 1; i <= n; i ++) {
		if (i >= m) {
			for (int j = 1; j <= k; j ++) {
				dp[i][j] = std::max(dp[i][j], dp[i - m][j - 1] + s[i] - s[i - m]);
				dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
			}
		}
	}
	std::cout << dp[n][k] << '\n';
}
```

# T2 (276D)

$l \le r \le 1e18$，求之间的两个数 $xor$ 的值最大，输出值。

诈骗题，只看最高的不相同的位区分$1000000$ 与$0111111$ ，答案显然。

```c++
void solve() {
	int l, r;
	std::cin >> l >> r;
	int i = (1ll << 60);
	while (i && (i & l) == (i & r)) {	//移位
		i >>= 1;
	}
	if (!i) {
		std::cout << 0 << '\n';
		return ;
	}
	std::cout << (i << 1) - 1 << '\n';
}
```

# T3 (1516C)

$n$个数，最少删除几个下标使之不会被分成两个子数组，$sum$ 相同。

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
	if (sum & 1) {
		std::cout << "0\n";
		return ;
	}
	sum /= 2;
	std::vector<int> d(n * 2000);
	d[0] = 1;
	for (int i = 0; i < n; i ++) {
		for (int j = sum; j >= v[i]; j --) {
			d[j] |= d[j - v[i]];
		}
	}
	if (! d[sum]) {
		std::cout << "0\n";
		return ;
	}
	// 奇数判别与01背包判断无需删除的状态。
	int ans = 0, res = 65;
	for (int i = 0; i < n; i ++) {
		int t = v[i], num = 0;
		while (t % 2 == 0) {
			num ++;
			t >>= 1;
		}
		if (num < res) {
			res = num;
			ans = i + 1;
		}
	}
	std::cout << 1 << '\n';
	std::cout << ans << '\n';
}
```

# T4 (1324E)

$n$次操作，初始值为$0$，每次操作$add \quad v_i \quad or \quad v_i - 1$，取模$h$，若落在$[l, r]$之间，则$ans + 1$，求$max$

```c++
void solve() {
	int n, h, l, r;
	std::cin >> n >> h >> l >> r;
	l %= h, r %= h;
	std::vector<int> v(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
	}
	std::vector<std::vector<int> > dp(n + 1, std::vector<int >(h, -INF));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i ++) {			//前 i day, on j hour get sleep
		for (int j = 0; j < h; j ++) {
			dp[i][j] = std::max({dp[i][j], 
  				(dp[i - 1][(j - v[i] + h) % h] + (j >= l && j <= r)), 	
                (dp[i - 1][(j - (v[i] - 1) + h) % h] + (j >= l && j <= r))});
		}
	}
	int ans = 0;
	for (int i = 0; i < h; i ++) {
		ans = std::max(ans, dp[n][i]);
	}
	std::cout << ans << '\n';
}
```

# T4 (546D)

分解质因子，阶乘形式，前$b$ 个数

```c++
	int N = 5e6 + 1;
	std::vector<bool> vis(N);
	std::vector<int> dp(N), p(N);
	int tot = 0;
	for (int i = 2; i < N; i ++) {
		if (! vis[i]) {
			p[++ tot] = i;
			dp[i] = 1;
		}
		for (int j = 1; j <= tot && i * p[j] < N; j ++) {
			vis[i * p[j]] = 1;
			dp[i * p[j]] = dp[i] + 1;
			if (i % p[j] == 0) {
				break;
			}
		}
	}
// dp[x] x have the number of fac
```

