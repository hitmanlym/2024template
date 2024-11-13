#include <bits/stdc++.h>
using i64 = long long;
const int N = 1030;
//std::bitset<10000> s;
//std::bitset<1000005> f[110];
std::bitset<N> f[2][N];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::bitset<4> s(std::string("1001"));//填充字符串
    //std::cout << s << '\n';
    int t = 5;
    std::bitset<10> k(t); //不足补零
    //std::cout << k << "\n";
    //std::bitset<1000>f[100]; //支持多维，代表有100个长度为1000的01串（默认为0）
    //s.count() 返回有多少个1
    //s.any() 至少有一个1返回true，反之false
    //s.none() 全为0返回true，反之false
    //s.set() 将每位全部赋值为1
    //s.set(u, v) 将第u位赋值为v， v只能取值0或者1
    //s.reset() 将每位全部赋值为0
    //s.reset(k) 将第k位赋值为0
    /*
    //example: 有n个数，x可以取值li-ri，问sumXi可能的值有多少。 (背包问题)

    // f[i] |= f[i - 1] << (x * x)
    int n;
    int l[110], r[110];
    std::cin >> n;
    for (int i = 1; i <= n; i ++) {
        std::cin >> l[i] >> r[i];
    }
    f[0].set(0);
    for (int i = 1; i <= n; i ++) {
        for (int j = l[i]; j <= r[i]; j ++) {
            f[i] |= (f[i - 1] << (j * j));
        }
    }
    std::cout << f[n].count() << "\n"; 
    */
    //example2: 优化DP时空复杂度； n个数，背包容量m，问装满背包时候，背包里面异或值最大可能是多少？
    //朴素方程 f[i][j][k] 前i个数，异或值为j，体积为k的方案是否存在 ， 滚动只能优化掉 一维 i,
    /*
        for (int j = tmp._Find_first(); j != tmp.size(); j = tmp._Find_next(j)) {
            ans[j] = i;
            q.reset(j);
        }
    找下一个 1 的 位置。
    */
    int T;
    std::cin >> T;
    while (T --) {
        int n, m;
        std::cin >> n >> m;
        for (int i = 0; i < 1024; i ++) f[0][i] = f[1][i] = 0;
        f[0][0][0] = 1;
        for (int i = 1, x = 1; i <= n; i ++, x ^= 1) {
            int v, w;
            std::cin >> v >> w;
            for (int j = 0; j < 1024; j ++) {
                f[x][j] = f[x ^ 1][j ^ w] << v | f[x ^ 1][j];
            }
        }
        int ok = -1;
        for (int i = 0; i < 1024; i ++)
            if (f[n & 1][i][m]) ok = i;
        std::cout << ok << "\n";
    }
	return 0;
}
