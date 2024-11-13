#include <bits/stdc++.h> // P3402 可持久化并查集 , 本质就是维护 fa 的可持久 + 按秩合并优化
using i64 = long long;
using f64 = double;

const int M = 2e5 + 5;
const i64 inf = -1e16;
int n, m;

i64 rt[M], tot;
struct ChairManTree {
    int lc, rc;
    int fa, dep;
}t[M << 5];

int find_version_fa(int p, int l, int r, int x) {
    if (l == r) return p;
    int mid = l + r >> 1;
    if (x <= mid) return find_version_fa(t[p].lc, l, mid, x);
    else return find_version_fa(t[p].rc, mid + 1, r, x);
}
int find(int u, int a) {
    int fa = find_version_fa(rt[u], 1, n, a);

    if (t[fa].fa == a) return fa;
    return find(u, t[fa].fa);   //  不要压缩！
}


int build(int l, int r) {
    int p = ++ tot;
    if (l == r) {
        t[p].fa = l;
        return p;
    }
    int mid = l + r >> 1;
    t[p].lc = build(l, mid);
    t[p].rc = build(mid + 1, r);
    return p;
}

int update(int pre, int l, int r, int x, int f) {
    int p = ++ tot;
    t[p] = t[pre];
    if (l == r) {
        t[p].fa = f;
        return p;
    }
    int mid = l + r >> 1;
    if (x <= mid) t[p].lc = update(t[pre].lc, l, mid, x, f);
    else t[p].rc = update(t[pre].rc, mid + 1, r, x, f);
    return p;
}
int add_dep(int pre, int l, int r, int x) {
    int p = ++ tot;
    t[p] = t[pre];
    if (l == r) {
        t[p].dep ++;
        return p;
    }
    int mid = l + r >> 1;
    if (x <= mid) t[p].lc = add_dep(t[pre].lc, l, mid, x);
    else t[p].rc = add_dep(t[pre].rc, mid + 1, r, x);
    return p;
}
void merge(int u, int a, int b) {
    rt[u] = rt[u - 1];

    a = find(u, a), b = find(u, b);
    if (t[a].fa == t[b].fa) return ;

    if (t[a].dep > t[b].dep) std::swap(a, b);
    rt[u] = update(rt[u], 1, n, t[a].fa, t[b].fa);

    if (t[a].dep == t[b].dep) {
        rt[u] = add_dep(rt[u], 1, n, t[b].fa);
    }
}
bool check(int u, int a, int b) {
    a = find(u, a), b = find(u, b);
    if (t[a].fa == t[b].fa) return 1;
    return 0;
}
int main() {
    std::cin >> n >> m;
    rt[0] = build(1, n);
    int op, a, b;
    for (int i = 1; i <= m; i ++) {
        std::cin >> op >> a;
        if (op == 2) {
            rt[i] = rt[a];
        } else if (op == 1) {
            std::cin >> b;
            merge(i, a, b);
        } else {
            std::cin >> b;
            bool ans = check(i - 1, a, b);
            std::cout << ans << '\n';

            rt[i] = rt[i - 1];
        }
    }
    return 0;
}