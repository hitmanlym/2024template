// #include<bits/stdc++.h>
#include<string>
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using i64 = long long;
std::vector<int> kmp(std::string s) {
	int n = s.size();
	std::vector<int> f(n + 1);
	for (int i = 1, j = 0; i < n; i ++) {
		while (j && s[i] != s[j]) {
			j = f[j];
		}
		j += (s[i] == s[j]);
		f[i + 1] = j;
	}
	return f;
}
void solve() {
	std::string s, t;
	std::cin >> t >> s;
	auto p = kmp(t);

	int n = s.size(), m = t.size();
	std::vector<int> pre(n + 4), sub(n + 4), pret(m + 2);
	// for(int i = 1; i <= m; i ++)
	// 	pret[i - p[i] + 1] = p[i];

	// std::cout << "pret:\n";
	// for(int i = 1;i <= m; i ++)
	// 	std::cout << pret[i] << ' ';
	// std::cout<< '\n';

	std::string a = " #" + s + "#", b = " " + t;
	n += 2;
	for (int i = 1, j = 0; i <= n; i ++) {
		while (j && a[i] != b[j + 1]) {
			pre[i - j] = j;
			// for(int k = i - j + 1; k < i - p[j]; k ++)
			// 	pre[k] = pret[k - (i - j) + 1];
			j = p[j];
		}
		j += (a[i] == b[j + 1]);
		if (j == m) {
			// std::cout << i - m + 1 << '\n';
			pre[i - j + 1] = j;
			j = p[j];
		}
	}

	// std::cout << "pre:\n";
	// for(int i = 1; i <= n; i ++)
	// 	std::cout << pre[i] << ' ';
	// std::cout << "\n";

	std::reverse(t.begin(), t.end());
	p = kmp(t);
	// for(int i = 1; i <= m; i ++)
	// 	pret[i - p[i] + 1] = p[i];

	b = " " + t;
	for (int i = n, j = 0; i >= 1; i --) {
		while (j && a[i] != b[j + 1]) {
			sub[i + j] = j;
			// for(int k = i + j - 1; k > i + p[j]; k --)
			// 	sub[k] = pret[i + j - k + 1];
			j = p[j];
		}
		j += (a[i] == b[j + 1]);
		if (j == m) {
			// std::cout << i - m + 1 << '\n';
			sub[i + j - 1] = j;
			j = p[j];
		}
	}

	// std::cout << "sub:\n";
	// for(int i = 1; i <= n; i ++)
	// 	std::cout << sub[i] << ' ';
	// std::cout << '\n';

	int now = 1, ans = 0;
	while(now <= n){
		if(!pre[now]){
			now++;
			continue;
		}
		int x = now - 1, y = now;
		if(pre[now] == m)
			while(pre[y] == m && y + m <= n) y += m;
		ans += std::max((y + pre[y] - 1) - (x - sub[x] + 1) + 1 - m + 1, 0);
		now = y + pre[y];
	}

	std::cout << ans;
	std::cout << '\n';
} 
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}
