#include<stdio.h>
#include<math.h>

// f'(x) = cos(x) - x
// f''(x) = -sin(x) - 1 < 0
// f'(1) = 0���� f'(x) ���������Ե�����С����
// f(x) �� (1, 2) �����ݼ�
double f(double x) {
	return sin(x) - x * x / 2.0;
}
void solve() {
	double l = 1.0 + 1e-9, r = 2.0 - 1e-9;
	while (r - l > 0.5 * 1e-5) { // �������f(x) >= 0 ��λ�ã� 
								// ��� f(mid) >= 0����ζ�� x �� (mid, r) ֮��
								// ����x �� (l, mid) ֮��  
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
