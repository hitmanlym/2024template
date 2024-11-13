#include<stdio.h>
#include<math.h>

// f'(x) = cos(x) - x
// f''(x) = -sin(x) - 1 < 0
// f'(1) = 0，又 f'(x) 单减，所以导数恒小于零
// f(x) 在 (1, 2) 单调递减
double f(double x) {
	return sin(x) - x * x / 2.0;
}
void solve() {
	double l = 1.0 + 1e-9, r = 2.0 - 1e-9;
	while (r - l > 0.5 * 1e-5) { // 二分最后f(x) >= 0 的位置， 
								// 如果 f(mid) >= 0，意味着 x 在 (mid, r) 之间
								// 否则，x 在 (l, mid) 之间  
		double mid = (l + r) / 2.0;
		if (f(mid) >= 0) {
			l = mid;
		} else {
			r = mid;
		}
	}
	printf("%.6lf\n", l);
}
int main() {
	int t = 1;
	while (t --) {
		solve();
	}
	return 0;
}
