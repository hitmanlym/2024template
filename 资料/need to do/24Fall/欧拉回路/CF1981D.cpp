#include<bits/stdc++.h>
using i64 = long long;

std::vector<int> minp, primes;
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}
const int N = 1e6;
std::vector<i64> max(N);
void solve() {
    int n;
    std::cin >> n;
    int num = std::lower_bound(max.begin(), max.end(), n) - max.begin();
    //std::cout << num << '\n';
    std::vector<std::vector<std::array<int, 2> > > e(num + 1);
    int cnt = 0;
    for (int i = 1; i <= num; i ++) {
        for (int j = i; j <= num; j ++) {
            if (num % 2 == 0 && i % 2 == 0 && i + 1 == j) {
                continue;
            }
            e[i].push_back({j, ++ cnt});
            e[j].push_back({i, cnt});
        }
    }

    std::vector<int> res, cur(num + 1);
    std::vector<bool> vis(cnt + 1);
    auto dfs = [&](auto self, int u) -> void {
        for (int &i = cur[u]; i < e[u].size(); ) {
            auto it = e[u][i ++];
            if (! vis[it[1]]) {
                vis[it[1]] = 1;
                self(self, it[0]);
            }
        }
        res.push_back(primes[u - 1]);
    };
    dfs(dfs, 1);
    std::reverse(res.begin(), res.end());
    for (int i = 0; i < n; i ++) {
        std::cout << res[i] << ' ';
    }
    std::cout << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    sieve(N);
    for (int i = 1; i < N; i ++) {
        if (i & 1) max[i] = 1ll * i * (i + 1) / 2 + 1; // 路径数 + 1
        else {
            max[i] = 1ll * i * i / 2 + 1 + 1;
        }
    }
    int t = 1;
    std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}