#include<bits/stdc++.h>
using i64 = long long;
#define int i64
const int mod = 1e9 + 7;
bool dp[201][201][5], op[5][5][5];
void solve() {
	std::map<char, int> mp;
    mp['W'] = 1;
    mp['I'] = 2;
    mp['N'] = 3;
    mp['G'] = 4;
    std::map<int, char> rev;
    rev[1] = 'W';
    rev[2] = 'I';
    rev[3] = 'N';
    rev[4] = 'G';
    std::vector<int> v(5);
    for (int i = 1; i <= 4; i ++) {
        std::cin >> v[i];
    }

    for (int i = 1; i <= 4; i ++) {
        for (int j = 1; j <= v[i]; j ++) {
            std::string s;
            std::cin >> s;
            op[mp[s[0]]][mp[s[1]]][i] = 1;
        }
    }
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        a[i] = mp[s[i - 1]];
    }

    for (int i = 1; i <= n; i ++) {
        dp[i][i][a[i]] = 1;
    }
    for (int len = 2; len <= n; len ++) {
        for (int l = 1, r; r = l + len - 1, r <= n; l ++) {
            for (int k = l; k < r; k ++) {

                for (int x = 1; x <= 4; x ++) {
                    for (int y = 1; y <= 4; y ++) {
                        for (int z = 1; z <= 4; z ++) {
                            if (dp[l][k][x] && dp[k + 1][r][y] && op[x][y][z]) {
                                dp[l][r][z] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    bool f = 0;
    for (int i = 1; i <= 4; i ++) {
        if (dp[1][n][i]) {
            f = 1;
            std::cout << rev[i];
        }
    }
    if (! f) {
        std::cout << "The name is wrong!\n";
    }
}
signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}