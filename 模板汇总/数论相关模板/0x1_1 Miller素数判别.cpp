using i64 = long long;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

std::vector<int> ans;

struct {
	ll qmul(ll a, ll b, ll mod) {
	    ll c = (ld)a / mod * b;
	    ll res = (ull)a * b - (ull)c * mod;
	    return (res + mod) % mod;
	}
	ll qpow(ll a, ll n, ll mod) {
	    ll res = 1;
	    while (n) {
	        if (n & 1) {
	        	res = qmul(res, a, mod);
	        }
	        a = qmul(a, a, mod);
	        n >>= 1;
	    }
	    return res;
	}
	bool MRtest(ll n) {//Miller Rabin Test
	    if (n < 3 || n % 2 == 0) return n == 2;
	    ll u = n - 1, t = 0;
	    while (u % 2 == 0) {
	    	u /= 2;
	     	++ t;
	    }
	    ll ud[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	    for (ll a : ud) {
	        ll v = qpow(a, u, n);
	        if (v == 1 || v == n - 1 || v == 0) {
	        	continue;
	        }
	        for (int j = 1; j <= t; j ++) {
	            v = qmul(v, v, n);
	            if (v == n - 1 && j != t) {
	            	v=1;
	            	break;
	            }
	            if (v == 1) {
	            	return 0;
	            }
	        }
	        if (v != 1) {
	        	return 0; //Fermat检验
	        }
	    }
	    return 1;
	}
}ty;