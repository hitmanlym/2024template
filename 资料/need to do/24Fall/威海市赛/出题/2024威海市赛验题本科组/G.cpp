#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	std::string s;
	std::cin >> s;
	s = " " + s + "$";
	std::map<std::string, int> S_total;
	std::map<std::string, int> it;
	for (int i = 3; i < s.size(); i ++) {
		std::string t = "";
		t += s[i - 2];
		t += s[i - 1];
		S_total[t] ++;
		t += s[i];
		it[t] ++;
	}
	double ans = 0.0;
	for (int i = 3; i < s.size(); i ++) {
		std::string t = "";
		int x, y;
		t += s[i - 2];
		t += s[i - 1];
		y = S_total[t];
		t += s[i];
		x = it[t];
		//std::cout << x<< ' ' << y << '\n';
		ans += log((double)x / y);
	}
	printf("%.10lf\n", ans);
}
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}