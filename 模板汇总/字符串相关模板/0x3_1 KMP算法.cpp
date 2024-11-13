#include<bits/stdc++.h>
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
	std::cin >> s >> t;
	auto p = kmp(t);

	int n = s.size(), m = t.size();

	std::string a = " " + s, b = " " + t;
	for (int i = 1, j = 0; i <= n; i ++) {
		while (j && a[i] != b[j + 1]) {
			j = p[j];
		}
		j += (a[i] == b[j + 1]);
		if (j == m) {
			std::cout << i - m + 1 << '\n';
			j = p[j];
		}
	}
	for (int i = 1; i <= m; i ++) {
		std::cout << p[i] << ' ';
	}
	std::cout << '\n';
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
