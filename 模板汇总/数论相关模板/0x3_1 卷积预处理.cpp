// nlogn 卷积预处理

void Dirichlet(std::vector<int> &f, std::vector<int>& g) {
    int n = f.size();
    std::vector<int> h(n + 1);
    for (int i = 1; i <= n; i ++) {
        for (int j = i; j <= n; j += i) {
            h[j] = (h[j] + f[i] * g[j / i]) % mod;
        }
    }
    for (int i = 1; i <= n; i ++) {
        f[i] = h[i];
    }
}