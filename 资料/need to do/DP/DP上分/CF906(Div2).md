# CF906(Div2)

## A

$a_1 + a_2 = a_2 + a_3 + ... = a_{n - 1} + a_n = k$，求给出的数组是否满足。

> 容易发现，只能有$2$种元素，且个数相差不超过$1$。

## B.C

字符串：$s_i \neq s_{n - i + 1},i = 1, 2, ... n$。给出$01$字符串$s$，操作：在任意插入$01$，求操作。

> 容易发现，利用双指针法，讨论相同的首末位置，分情况加在前面或后面。

```c++
void solve() {
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	int num = 0;
	for (int i = 0; i < n; i ++) {
		if (s[i] == '0') num ++;
	}
	if (n & 1 || num != n / 2) {
		std::cout << -1 << '\n';
		return ;
	}
	std::vector<int> v;
	int l = 0, r = n - 1;
	while (l <= r) {
		if (s[l] == s[r]) {
			if (s[l] == '0') {
				s = s.substr(0, r + 1) + "01" + s.substr(r + 1);
				v.push_back(r + 1);
				r += 2;
				n += 2;
			} else {
				s = s.substr(0, l) + "01" + s.substr(l, r - l + 1);
				v.push_back(l);
				r += 2;
				n += 2;
			}
		}
		l ++, r --;
	}
	std::cout << v.size() << '\n';
	for (auto it : v) {
		std::cout << it << ' ';
	}
	std::cout << '\n';
}
```

## D

给出$n$个顶点，每个顶点有权值$a_i$，对顶点$i, j$连边：$\underset{k \in S}{\sum}{a_k} \ge i \cdot j \cdot c$，$S$为$i, j$所在集合的所有顶点。

求是否连通。

> 分析由$1$号顶点：$a_1 \ge j \cdot c - a_j$，$a_1$不断吸收，只需要将$2 到 n$排序后依次check即可。

```c++
void solve() {
	int n, c;
	std::cin >> n >> c;
	std::vector<std::pair<int, int> > v(n + 1,std::pair<int, int>());
	for (int i = 1; i <= n; i ++) {
		std::cin >> v[i].first;
		v[i].second = i * c - v[i].first;
	}
	std::sort(v.begin() + 2, v.end(), [&](std::pair<int, int> a, std::pair<int, int> b) {
		return a.second < b.second;
	});
	int sum = v[1].first;
	for (int i = 2; i <= n; i ++) {
		if (sum < v[i].second) {
			std::cout << "No\n";
			return ;
		}
		sum += v[i].first;
	}
	std::cout << "Yes\n";
}
```

  



