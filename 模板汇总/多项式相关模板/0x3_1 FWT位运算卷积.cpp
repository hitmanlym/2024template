#include<bits/stdc++.h>
using i64 = long long;
using Poly = std::vector<int>;
const int N = 5e4 + 10, P = 998244353;

struct FWT {
    void add(int &x, int y) {
        (x += y) >= P && (x -= P);
    }
    void sub(int &x, int y) {
        (x -= y) < 0 && (x += P);
    }
    int extend(int n) {
        int N = 1;
        for (; N < n; N <<= 1);
        return N;
    }
    void FWTor(Poly &a, bool rev) {
        int n = a.size();
        for (int l = 2, m = 1; l <= n; l <<= 1, m <<= 1) {
            for (int j = 0; j < n; j += l) for (int i = 0; i < m; i++) {
                if (!rev) add(a[i + j + m], a[i + j]);
                else sub(a[i + j + m], a[i + j]);
            }
        }
    }
    void FWTand(Poly &a, bool rev) {
        int n = a.size();
        for (int l = 2, m = 1; l <= n; l <<= 1, m <<= 1) {
            for (int j = 0; j < n; j += l) for (int i = 0; i < m; i++) {
                if (!rev) add(a[i + j], a[i + j + m]);
                else sub(a[i + j], a[i + j + m]);
            }
        }
    }
    void FWTxor(Poly &a, bool rev) {
        int n = a.size(), inv2 = (P + 1) >> 1;
        for (int l = 2, m = 1; l <= n; l <<= 1, m <<= 1) {
            for (int j = 0; j < n; j += l) for (int i = 0; i < m; i++) {
                int x = a[i + j], y = a[i + j + m];
                if (!rev) {
                    a[i + j] = (x + y) % P;
                    a[i + j + m] = (x - y + P) % P;
                } else {
                    a[i + j] = 1LL * (x + y) * inv2 % P;
                    a[i + j + m] = 1LL * (x - y + P) * inv2 % P;
                }
            }
        }
    }
    Poly Or(Poly a1, Poly a2) {
        int n = std::max(a1.size(), a2.size()), N = extend(n);
        a1.resize(N), FWTor(a1, false);
        a2.resize(N), FWTor(a2, false);
        Poly A(N);
        for (int i = 0; i < N; i++) A[i] = 1LL * a1[i] * a2[i] % P;
        FWTor(A, true);
        return A;
    }
    Poly And(Poly a1, Poly a2) {
        int n =  std::max(a1.size(), a2.size()), N = extend(n);
        a1.resize(N), FWTand(a1, false);
        a2.resize(N), FWTand(a2, false);
        Poly A(N);
        for (int i = 0; i < N; i++) A[i] = 1LL * a1[i] * a2[i] % P;
        FWTand(A, true);
        return A;
    }
    Poly Xor(Poly a1, Poly a2) {
        int n = std::max(a1.size(), a2.size()), N = extend(n);
        a1.resize(N), FWTxor(a1, false);
        a2.resize(N), FWTxor(a2, false);
        Poly A(N);
        for (int i = 0; i < N; i++) A[i] = 1LL * a1[i] * a2[i] % P;
        FWTxor(A, true);
        return A;
    }
} fwt;

void solve() { // n = 2 ^ m 个数.
    int n, m;
    std::cin >> m;
    n = 1 << m;
    Poly a1(n), a2(n);
    for (int i = 0; i < n; i ++) std::cin >> a1[i];
    for (int i = 0; i < n; i ++) std::cin >> a2[i];
    Poly A;
    A = fwt.Or(a1, a2);
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << ' ';
    }
    std::cout << '\n';
    A = fwt.And(a1, a2);
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << ' ';
    }
    std::cout << '\n';
    A = fwt.Xor(a1, a2);
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << ' ';
    }
    std::cout << '\n';
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}
