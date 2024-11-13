#include<bits/stdc++.h>
using i64 = long long;

int BSGS(int a, int b, int p) {
    if (1ll % p == b % p) return 0;
    int k = std::sqrt(p) + 1;
    std::unordered_map<int, int> hash;
    for (int i = 0, j = b % p; i < k; i ++) {
        hash[j] = i; 
        j = 1ll * j * a % p;
    }
    int ak = 1;
    for (int i = 0; i < k; i ++) {
        ak = 1ll * ak * a % p;
    } 
    for (int i = 1, j = ak; i <= k; i ++) {
        if (hash.count(j)) return 1ll * i * k - hash[j];
        j = 1ll * j * ak % p;
    }
    return -1;
}

void solve() {
    int a, p, b;
    std::cin >> p >> a >> b; // a^x = b (mod p) [a-p]
    int res = BSGS(a, b, p);
    if (res == -1) {
        std::cout << "no solution\n";
    } else {
        std::cout << res << '\n';
    }
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