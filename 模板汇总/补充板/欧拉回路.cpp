void solve() {
    int m;
    std::cin >> m;
    std::vector<std::vector<pii> > e(N + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back({v, i});
        e[v].push_back({u, i});
    } 
    int st = 0;
    for (int i = 1; i <= N; i ++) {
        std::sort(e[i].begin(), e[i].end());
        if (e[i].size() && ! st) st = i;
    }
    for (int i = 1; i <= N; i ++) {
        if (e[i].size() & 1) {
            st = i;
            break;
        }
    }
    std::vector<int> cur(N + 1);
    std::vector<bool> vis(m + 1);
    std::vector<int> res;
    auto dfs = [&](auto self, int u) -> void {
        for (int &i = cur[u]; i < e[u].size(); ) {
            auto nt = e[u][i ++];
            if (! vis[nt[1]]) {
                vis[nt[1]] = 1;
                self(self, nt[0]);
            }
        }
        res.push_back(u);
    };
    dfs(dfs, st);
    std::reverse(res.begin(), res.end());
    for (auto it : res) {
        std::cout << it << '\n';
    }
}
////有向图
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > e(n + 1);
    std::vector<int> in(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        e[u].push_back(v);
        in[v] ++;
    } 
    bool flag = 1;
    int st = 0;
    for (int i = 1; i <= n; i ++) {
        std::sort(e[i].begin(), e[i].end());
        if (std::abs((int)e[i].size() - in[i]) > 1) {
            flag = 0;
        }
        if (e[i].size() > in[i]) {
            if (st) flag = 0;
            st = i;
        }
    }
    if (! st) st = 1;
    std::vector<int> cur(n + 1);
    std::vector<int> res;
    auto dfs = [&](auto self, int u) -> void {
        for (int &i = cur[u]; i < e[u].size(); ) {
            self(self, e[u][i ++]); // attention please.
        }
        res.push_back(u);
    };
    dfs(dfs, st);
    if (res.size() != m + 1) {
        flag = 0;
    }
    if (! flag) {
        std::cout << "No\n";
    } else {
        std::reverse(res.begin(), res.end());
        for (auto it : res) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
    }
}
// 混合图，利用出度 = d[i] / 2 建立网络流模型, 边， 点（此边从谁而出）