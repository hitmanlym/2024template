#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
using i64 = long long;

#define ull unsigned long long
const int M = 2e7 + 5;
int ls[M], rs[M], rt[M];
ull cnt[M], sum[M], sqr[M], ans[M];
void solve()
{
	int n;
    std::cin >> n;
    std::vector<std::vector<int>> E(n + 1);
    for (int i = 1; i < n; ++i)
    {
    	int u, v;
        std::cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    std::vector<int> id(n + 1), A(n + 1);
    for (int i = 1; i <= n; ++i) {
    	std::cin >> A[i];
    	id[i] = i;
    }
    std::sort(id.begin() + 1, id.end(), [&](int x, int y){return A[x] < A[y];});
    std::vector<int> rk(n + 1);
    for (int i = 1; i <= n; ++i)
        rk[id[i]] = i;
    int num = 0;
    std::vector<int> rt(n + 1);
    std::vector<ull> ans(n + 1);
    auto push_up = [&](int p)
    {
        cnt[p] = cnt[ls[p]] + cnt[rs[p]];
        sum[p] = sum[ls[p]] + sum[rs[p]];
        sqr[p] = sqr[ls[p]] + sqr[rs[p]];
    };
    bool flag = 0;
    auto Update = [&](auto self, int &p, int l, int r, int x, ull y) -> void
    {
        if (!p)
            p = ++num;
        if (l == r)
        {
            cnt[p] = 1;
            sum[p] = y;
            sqr[p] = y * y;
            return;
        }
        int mid = l + r >> 1;
        if (x <= mid)
            self(self, ls[p], l, mid, x, y);
        else
            self(self, rs[p], mid + 1, r, x, y);
        push_up(p);
    };
    auto Merge = [&](auto self, int &p, int q, int l, int r, ull has1, ull pre1, ull has2, ull pre2) -> ull
    {
        if (!p || !q || l == r)
        {
            ull L = has1 * sqr[q] - pre1 * sum[q];
            ull R = has2 * sqr[p] - pre2 * sum[p];
            //就是上面推出的那个式子对于两边都算贡献
            if (!p) p = q;
            else cnt[p] += cnt[q], sum[p] += sum[q], sqr[p] += sqr[q];
            return L + R;
        }
        int mid = l + r >> 1;
        //先r后l的原因是先更新左边的话，cnt[ls[q]]可能会变
        ull R = self(self, rs[p], rs[q], mid + 1, r, has1 + cnt[ls[p]], pre1 + sum[ls[p]], has2 + cnt[ls[q]], pre2 + sum[ls[q]]);
        ull L = self(self, ls[p], ls[q], l, mid, has1, pre1, has2, pre2);
        push_up(p);
        return L + R;
    };
    auto dfs = [&] (auto self, int u, int f) -> void
    {
        Update(Update, rt[u], 1, n, rk[u], A[u]);
        for (int v : E[u])
            if (v ^ f)
            {
                self(self, v, u);
                ans[u] += Merge(Merge, rt[u], rt[v], 1, n, 0, 0, 0, 0);
                ans[u] += ans[v];
                flag = 0;
            }
    };
    dfs(dfs, 1, 0);
    ull res = 0;
    for (int i = 1; i <= n; ++i)
        res ^= ans[i] << 1;
    std::cout << res << '\n';
}

// x, x_sum, x^2, x^2_sum, 1, num_sum
int main() { 
	//freopen("input.in", "r", stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}
/*

10
1 2
2 3
3 4
1 5
4 6
1 7
5 8
4 9
9 10

1000000 1000000 1000000 1 1000000 1 1 1 1000000 1
*/