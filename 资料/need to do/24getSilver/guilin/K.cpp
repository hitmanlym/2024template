#include<bits/stdc++.h>
using namespace std;

void solve()
{
	int n, m; cin >> n >> m;
	if (n % 2 == 0 && m % 2 == 0)
	{
		if (m < n)cout << "NO" << endl;
		else {
			cout << "YES" << endl;
			for (int i = 1; i <= n - 2; ++i)cout << 1 << " ";
			cout << (m - n + 2) / 2 << " " << (m - n + 2) / 2 << endl;
		}
		return;
	}
	if (n % 2 == 0 && m % 2 != 0)
	{
		if (2 * n + 1 > m)cout << "NO" << endl;
		else {
			cout << "YES" << endl;
			cout << 3 << " " << 2 << " ";
			for (int i = 3; i <= n - 2; ++i)cout << 2 << " ";
			if (n >= 4)cout << (m - 2 * (n - 2)) / 2 << " " << (m - 2 * (n - 2)) / 2;
			cout << endl;
		}
		return;
	}
	if (n % 2 == 1 && m % 2 == 0)
	{
		if (n == 1)cout << "NO" << endl;
		else {
			n = n - 3; m = m - 6;
			if (m < n)cout << "NO" << endl;
			else {
				cout << "YES" << endl;
				cout << 1 << " " << 2 << " " << 3 << " ";
				for (int i = 1; i <= n - 2; ++i)cout << 1 << " ";
				cout << (m - n + 2) / 2 << " " << (m - n + 2) / 2 << endl;
			}
		}
		return;
	}
	if (n % 2 == 1 && m % 2 == 1)
	{
		if (n == 1)cout << "NO" << endl;
		else {
			n = n - 3; m = m - 13;
			if (m < 2*n)cout << "NO" << endl;
			else {
				cout << "YES" << endl;
				cout << 3 << " " << 4 << " " << 6 << " ";
				for (int i = 1; i <= n - 2; ++i)cout << 2 << " ";
				cout << (m - 2*n + 4) / 2 << " " << (m - 2*n + 4) / 2 << endl;
			}
		}
		return;
	}
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	int t=1; cin >> t;
	while (t--) {
		solve();
	}
}