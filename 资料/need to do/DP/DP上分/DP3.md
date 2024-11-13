# T1 (1335E)

$[\underbrace{a,a,a,a}_{x},\underbrace{b,b,b,b}_{y},\underbrace{a,a,a,a}_{x}]$

将一组数取最长的子序列长度。

```c++
void solve() {
	int n;
	std::cin >> n;
	std::vector<int> v(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i];
	}
	std::vector<std::vector<int> > e(n + 1, std::vector<int> (201));
	std::vector<std::vector<int> > b(201, std::vector<int>());
	int ans = 0;
	for (int i = 1; i <= n; i ++) {
		b[v[i]].push_back(i);
		for (int j = 1; j < 201; j ++) {
			e[i][j] = e[i - 1][j];
		}
		e[i][v[i]] ++;
		ans = std::max(ans, e[i][v[i]]);
	}
	for (int i = 1; i <= n; i ++) {
		int x = e[i][v[i]];

		int l = i + 1, r = b[v[i]][b[v[i]].size() - x] - 1;	//掐中间，取两边。
		if (l > r) continue;
		for (int j = 1; j < 201; j ++) {
			ans = std::max(ans, e[r][j] - e[l - 1][j] + x * 2);
		}
	}
	std::cout << ans << '\n';
}
```

# T2 (1695C)

![img](https://espresso.codeforces.com/ec89cd08933aec8a8d885927c0806a556ed1f6ed.png)

$n * m$格子，包含$1\quad or \quad -1$，从$(1,1)$到$(n, m)$，每次往右或往下走，是否能和为$0$。

```c++
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int> > g(n + 1, std::vector<int>(m + 1));
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			std::cin >> g[i][j];
		}
	}
	int sum = n + m - 1;
	if (sum & 1) {							//odd - impossible
		std::cout << "NO\n";
		return ;
	}
	std::vector<std::vector<int> > min(n + 1, std::vector<int>(m + 1, n + m));
	std::vector<std::vector<int> > max(n + 1, std::vector<int>(m + 1, - n - m));
	min[1][1] = max[1][1] = (g[1][1] == 1);	//if between max-min ,ok!
	sum /= 2;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			min[i][j] = std::min({min[i][j], 
                                  min[i - 1][j] + (g[i][j] == 1), 
                                  min[i][j - 1] + (g[i][j] == 1)});
			max[i][j] = std::max({max[i][j], 
                                  max[i - 1][j] + (g[i][j] == 1), 
                                  max[i][j - 1] + (g[i][j] == 1)});
		}
	}
	if (sum >= min[n][m] && sum <= max[n][m]) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
	}
}
```

