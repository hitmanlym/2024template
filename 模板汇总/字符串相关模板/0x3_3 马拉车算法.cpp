#include<bits/stdc++.h>
using i64 = long long;

std::vector<int> manacher(std::string s) {
    std::string t = "#";
    for (auto c : s) {
        t += c;
        t += '#';
    }
    int n = t.size();
    std::vector<int> r(n);
    for (int i = 0, j = 0; i < n; i ++) {
        if (2 * j - i >= 0 && j + r[j] > i) {
            r[i] = std::min(r[2 * j - i], j + r[j] - i);
        }
        while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]]) {
            r[i] += 1;
        }
        if (i + r[i] > j + r[j]) {
            j = i;
        }
    }
    return r; // radius
    // 结论 rad[l + r] 是区间 [l, r) 的中间位置的回文长度 + 1。
}
void solve() {
    std::string s;
    std::cin >> s;
    auto it = manacher(s);
    int ans = 0;
    for (auto x : it) {
        ans = std::max(ans, x - 1);
    }
    std::cout << ans << '\n';
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}