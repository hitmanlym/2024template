int qmi(int a, int b = mod - 2) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int qmul(int a, int b) {
    if (b < 0) a = -a, b = -b;
    int res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

// 大数 快速幂 在 page 36.