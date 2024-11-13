#include<bits/stdc++.h>
using i64 = long long;
void solve() {
	int n,k;
	std::cin >> n >> k;
	if((n & 1) || (k >= n)) {
		std::cout << "Alice\n";
		return;
	}
	int mi = 1;
	while(n % 2 == 0){
		n /= 2;
		mi *= 2;
	}
	if(k < mi) {
		std::cout << "Bob\n";
	}else std::cout << "Alice\n";
}
int main() {
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}