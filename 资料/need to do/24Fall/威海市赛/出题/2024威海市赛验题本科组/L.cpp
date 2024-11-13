#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	std::string s;
	std::cin >> s;
	int l = 0;
	std::vector<std::vector<char> > mp(9, std::vector<char>(9));
	std::array<int, 2> w, b;
	for (int i = 1; i <= 8; i ++) {
		int j = 1;
		while (j <= 8) {
			char c = s[l];
			l ++;
			if (c >= '0' && c <= '9') {
				int it = c - '0';
				while (it --) {
					mp[i][j ++] = '#';
				}
			} else {
				mp[i][j ++] = c;
				if (c == 'K') {
					w = {i, j - 1};
				} 
				if (c == 'k') {
					b = {i, j - 1};
				}
			}
		}
		l ++;
	}/*
	for (int i = 1; i <= 8; i ++) {
		for (int j = 1; j <= 8; j ++) {
			std::cout << mp[i][j];
		}
		std::cout << '\n';
	}*/
	auto print1 = [&]() {
		std::cout << "check\n";
		return;
	};
	auto print2 = [&]() {
		std::cout << "CHECK\n";
		return;
	};
	for (int i = 1; i <= 8; i ++) {
		for (int j = 1; j <= 8; j ++) {
			if (mp[i][j] >= 'a' && mp[i][j] <= 'z') {
				if (mp[i][j] == 'r') { // 车
					if (w[0] == i || w[1] == j) {
						bool f = 1;
						if (w[0] == i) {
							for (int k = std::min(w[1], j) + 1; k <= std::max(w[1], j) - 1; k ++) {
								if (mp[i][k] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[1] == j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][j] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (f) {
							print1();
							return ;
						}
					}
				} else if (mp[i][j] == 'n') { // 马
					if (std::abs(w[0] - i) == 2 && std::abs(w[1] - j) == 1 || 
						std::abs(w[1] - j) == 2 && std::abs(w[0] - i) == 1) {
						print1();
						return ;
					}	
				} else if (mp[i][j] == 'b') {	// 象
					if (w[0] + w[1] == i + j || w[0] - w[1] == i - j) {
						bool f = 1;
						if (w[0] + w[1] == i + j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][i + j - k] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[0] - w[1] == i - j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][k - (i - j)] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (f) {
							print1();
							return ;
						}
					}
				} else if (mp[i][j] == 'q') { 	// 皇后
					if (w[0] == i || w[1] == j 
						|| w[0] + w[1] == i + j 
						|| w[0] - w[1] == i - j) {
						bool f = 1;
						if (w[0] == i) {
							for (int k = std::min(w[1], j) + 1; k <= std::max(w[1], j) - 1; k ++) {
								if (mp[i][k] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[1] == j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][j] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[0] + w[1] == i + j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][i + j - k] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[0] - w[1] == i - j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][k - (i - j)] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (f) {
							print1();
							return ;
						}
					}
				} else if (mp[i][j] == 'p') {	// 兵
					if (w[0] == i + 1 && std::abs(w[1] - j) == 1) {
						print1();
						return ;
					}
				}
			}
		}
	}
	w = b;
	for (int i = 1; i <= 8; i ++) {
		for (int j = 1; j <= 8; j ++) {
			if (mp[i][j] != '#') mp[i][j] += 'a' - 'A';
			if (mp[i][j] >= 'a' && mp[i][j] <= 'z') {
				if (mp[i][j] == 'r') { // 车
					if (w[0] == i || w[1] == j) {
						bool f = 1;
						if (w[0] == i) {
							for (int k = std::min(w[1], j) + 1; k <= std::max(w[1], j) - 1; k ++) {
								if (mp[i][k] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[1] == j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][j] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (f) {
							print2();
							return ;
						}
					}
				} else if (mp[i][j] == 'n') { // 马
					if (std::abs(w[0] - i) == 2 && std::abs(w[1] - j) == 1 || 
						std::abs(w[1] - j) == 2 && std::abs(w[0] - i) == 1) {
						print2();
						return ;
					}	
				} else if (mp[i][j] == 'b') {	// 象
					if (w[0] + w[1] == i + j || w[0] - w[1] == i - j) {
						bool f = 1;
						if (w[0] + w[1] == i + j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][i + j - k] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[0] - w[1] == i - j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][k - (i - j)] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (f) {
							print2();
							return ;
						}
					}
				} else if (mp[i][j] == 'q') { 	// 皇后
					if (w[0] == i || w[1] == j 
						|| w[0] + w[1] == i + j 
						|| w[0] - w[1] == i - j) {
						bool f = 1;
						if (w[0] == i) {
							for (int k = std::min(w[1], j) + 1; k <= std::max(w[1], j) - 1; k ++) {
								if (mp[i][k] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[1] == j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][j] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[0] + w[1] == i + j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][i + j - k] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (w[0] - w[1] == i - j) {
							for (int k = std::min(w[0], i) + 1; k <= std::max(w[0], i) - 1; k ++) {
								if (mp[k][k - (i - j)] != '#') {
									f = 0;
									break;
								}
							}
						}
						if (f) {
							print2();
							return ;
						}
					}
				} else if (mp[i][j] == 'p') {	// 兵
					if (w[0] == i - 1 && std::abs(w[1] - j) == 1) {
						print2();
						return ;
					}
				}
			}
		}
	}
	std::cout << "none\n";
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