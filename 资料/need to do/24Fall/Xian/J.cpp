#include<bits/stdc++.h>
void solve() {
	int t, n, k, x, y;
	std::cin >> t >> n >> k >> x >> y;
	if (x > y) {
		std::swap(x, y);
	}
	auto print = [&]() -> void {
		std::cout << y - x << '\n';
	};
	auto wa = [&]() -> void {
		std::cout << -1 << '\n';
	};
	auto ac = [&]() -> void {
		std::cout << 1 << '\n';
	};

	if (! t) {
		print();
		return ;
	} else if (t == 1) {
		if (y - x >= k) {
			ac();
		} else if (y <= n - k || x >= k + 1) {
			std::cout << 2 << '\n';
		} else if (x > n - k && x < k + 1 || y > n - k && y < k + 1) { 
			wa();
		} else {
			std::cout << 3 << '\n';
		}/*
			else if (n - x >= k && y - 1 >= k) {
				std::cout << 3 << '\n';
			} else {
				wa();
			}*/

		// fix
		return ;
	}
	if (k == 1) {
		std::cout << 1 << '\n';
		return ;
	} 
	if (k == 2) {
		if (n == 2 || n == 3) {
			wa();
			return ;
		} else if (n == 4) {
			if (t & 1) {
				if (x == 2 && y == 3) {
					std::cout << 3 << '\n';
				} else if (x == 1 && y == 3 || x == 1 && y == 4 || x == 2 && y == 4) {
					ac();
				} else {
					std::cout << 2 << '\n';
				}
			} else {
				print();
			}
			return ;
		}
		if (t & 1) {
			std::cout << 1 + (y - x == 1) << '\n';
		} else {
			print();
		}
		return ;
	}
	if (k == 3) {
		if (n <= 4) {
			wa();
		} else if (n == 5) {
			if (t == 2) {
				if (x == 2 && y == 4) {
					ac();
				} else {
					wa();
				}
			} else {
				wa();
			}
		} else if (n == 6) { // t >= 2
			if (t == 2) { // 24 // 34 // 35
				if (x == 2 && y == 4 || x == 3 && y == 4 || x == 3 && y == 5) {
					ac();
				} else if (x == 2 && y == 3 || x == 4 && y == 5) {
					std::cout << 2 << '\n';
				} else if (x == 2 && y == 5) {
					std::cout << 3 << '\n';
				} else {
					wa();
				}
			} else if (t == 3) {
				if (x == 2 && y == 5) {
					ac();
				} else {
					wa();
				}
			} else {
				wa();
			}
		} else if (n == 7) {
			if (t == 2) {
				if (x == 3 && y == 5) {
					ac();
				} else {
					wa();
				}
			} else {
				wa();
			}
		}
	}
	if (k > 3) {
		wa();
	}
}
int main() {
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}