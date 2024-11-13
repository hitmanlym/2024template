#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define db(args...) { \
     string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
     stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); cout << '\n';}
void err(istream_iterator<string> it){}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << ' ';
    err(++it, args...);
}


void show(vector<int> a) {
    // int n = a.size();
    // for (int i = 1; i < n; i++) cout << a[i] << " \n" [i == n - 1];
}
void solve() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n + 1, -1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    auto tmp = a;

    auto add = [&] (int x, int y) {
        return x + y & 1;
    };
    auto mul = [&] (int x, int y) {
        return x * y;
    };

    auto del = [&] (int i, int ask = 0) {
        assert(a.size() > 2);
        if (ask) {
            if (i == 1) {
                if (add(a[i + 1], a[i]) == a[i + 1]) {
                    cout << i << ' ' << '+' << endl;
                } else {
                    cout << i << ' ' << '*' << endl;
                }
            } else {
                if (add(a[i - 1], a[i]) == a[i - 1]) {
                    cout << i - 1 << ' ' << '+' << endl;
                } else {
                    cout << i - 1 << ' ' << '*' << endl;
                }
            }
        }
        a.erase(a.begin() + i);
    };
    auto c1 = [&] (int id) {
        assert(a[id] == 1);
        int c = 0;
        for (int i = id + 1; i < a.size(); i++) {
            if (a[i] == 0) break;
            c++;
        }
        for (int i = id; i > 0; i--) {
            if (a[i] == 0) break;
            c++;
        }
        return c;
    };
    auto opt1 = [&] (int ask) {
        // 要1的一方的操作
        assert(a.size() > 2);
        bool ok = 0;
        for (int i = 1; i < a.size(); i++) {
            if (!ok && a[i] == 0 && (a[i - 1] != 1 || i == a.size() - 1 || a[i + 1] != 1)) {
                del(i, ask);
                ok = 1;
            }
            
        }
        for (int i = 2; i < a.size() - 1; i++) {
            if (!ok && a[i] == 0 && (a[i - 1] == 1 && a[i + 1] == 1 && (c1(i - 1) + c1(i + 1) & 1))) {
                del(i, ask);
                ok = 1;
            }
        }

        for (int i = 1; i < a.size(); i++) {
            if (!ok && a[i] == 0) {
                del(i, ask);
                ok = 1;
            }
        }
        if (!ok) {
            del((int)a.size() - 1, ask);
            ok = 1;
        }
    };

    auto change = [&] (int i, int ask) {
        assert(a[i] == a[i + 1] && a[i] == 1);
        if (ask) cout << i << " +" << endl;
        a.erase(a.begin() + i + 1);
        a[i] = 0;
    };

    auto opt0 = [&] (int ask) {
        // 要0的一方的操作
        assert(a.size() > 2);
        bool ok = 0;
        for (int i = 1; i < (int)a.size() - 1; i++) {
            if (!ok && a[i] == a[i + 1] && a[i] == 1) {
                change(i, ask);
                ok = 1;
                break;
            }
        }
        if (!ok) {
            for (int i = 1; i < a.size(); i++) {
                if (!ok && a[i] == 1) {
                    del(i, ask);
                    ok = 1;
                    break;
                }
            }
        }
        if (!ok) {
            del((int)a.size() - 1, ask);
            ok = 1;
        }
    };

    int turn = 0;
    while (a.size() - 1 >= 2) {
        if (turn == 0) {
            if (t == 0) opt0(0);
            else opt1(0);
        } else {
            if (t == 0) opt1(0);
            else opt0(0);
        }
        turn ^= 1;
    }
    assert(a.size() == 2);
    // cout << a[1] << '\n';

    auto get = [&] () {
        int i; char c;
        cin >> i >> c;
        assert(i);
        if (c == '+') {
            a[i] = add(a[i], a[i + 1]);
        } else {
            a[i] = mul(a[i], a[i + 1]);
        }
        a.erase(a.begin() + i + 1);
    };

    int xx = a[1];
    a = tmp;
    if (xx == t) {
        cout << "Alice" << endl;
        while (a.size() > 2) {
            if (t) opt1(1);
            else opt0(1);
            
            if (a.size() > 2) get();
        }
        assert(a[1] == t);
    } else {
        cout << "Bob" << endl;
        while (a.size() > 2) {
            if (a.size() > 2) get();
            if (a.size() > 2) {
                if (t) opt0(1);
                else opt1(1);
            }
        }
        assert(a[1] ^ t);
    }
    // cout << "end" << endl;
}
signed main() {
    // ios::sync_with_stdio(0); cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
/*
g++ 1.cpp -std=c++20 -o 1 && ./1 < in.txt > out.txt
g++ 1.cpp -std=c++20 -o 1 && ./1
*/