#pragma GCC optimize(2)
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<map>
using i64 = long long;

int O;
const int N = 2e6;
std::vector<int> mp(N);
struct AhoCorasick {
    int CNT;
    int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        int end; // 以之结尾的单词数
        std::vector<int> st;
        std::array<int, 26> next;
        Node() : link{}, next{} {}
    };
    
    std::vector<Node> t;
    
    AhoCorasick() {
        init();
    }
    
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
        t[1].next.fill(0);
        t[1].len = -1;
        t[1].end = 0;
        t[1].st.clear();
    }
    
    int newNode() {
        t.emplace_back();
        CNT = t.size() - 1;
        t[CNT].next.fill(0);
        t[CNT].end = 0;
        t[CNT].st.clear();
        return CNT;
    }
    
    int add(const std::vector<int> &a) {
        int p = 1;
        for (auto x : a) {
            if (t[p].next[x] == 0) {
                int rev = newNode();
                t[p].next[x] = rev;
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        t[p].st.push_back(O);
        return p;
    }
    
    int add(const std::string &a, char offset = 'a') { 
        std::vector<int> b(a.size());
        for (int i = 0; i < a.size(); i++) {
            b[i] = a[i] - offset;
        }
        return add(b);
    }
    
    void work() {
        std::queue<int> q;
        q.push(1);
        
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }
    
    void query(const std::string &s) { // end -| -1; trick; & 前缀和状态...
        
        int p = 1;
        for (auto c : s) {
            int op = c - 'a';
            p = t[p].next[op];
            t[p].end ++;
        }
    }

    std::vector<std::vector<int> > e;

    void INIT() {
        e.assign(CNT + 1, {});
    }
    void DFS(int u) {
        for (auto v : e[u]) {
            DFS(v);
            t[u].end += t[v].end;
        }
        for (auto it : t[u].st) {
            mp[it] += t[u].end;
        }
    }
    void LinkTree() { //  求解子树信息，来前缀优化，避免重复状态.
        INIT();
        for (int i = 1; i <= CNT; i ++) {
            e[t[i].link].push_back(i);
        }
        DFS(1);
        return ;
    }

    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int next(int p, char c, char offset = 'a') {
        return next(p, c - 'a');
    }
    
    int link(int p) {
        return t[p].link;
    }
    
    int len(int p) {
        return t[p].len;
    }
    
    int size() {
        return t.size();
    }
};
std::vector<int> kmp(std::string s) {
	int n = s.size();
	std::vector<int> f(n + 1);
	for (int i = 1, j = 0; i < n; i ++) {
		while (j && s[i] != s[j]) {
			j = f[j];
		}
		j += (s[i] == s[j]);
		f[i + 1] = j;
	}
	return f;
}

void solve() {
	int n;
	std::cin >> n;
	std::string s, t, x, y;
	std::cin >> s >> t;
	auto p = kmp(t);
	int m = t.size();
	t = " " + t;
	
	AhoCorasick ac;
	std::vector<int> count(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> x >> y;
		O = i;
		ac.add(x);
		int z = y.size();
		y = " " + y;
		bool f = 0;
		for (int i = 1, j = 0; i <= z; i ++) {
			while (j && y[i] != t[j + 1]) {
				j = p[j];
			}
			j += (y[i] == t[j + 1]);
			if (j == m) {
				f = 1;
				break;
			}
		}
		if (f) {
			count[i] = 1;
		}
	}
	ac.work();
	ac.query(s);
	ac.LinkTree();
	for (int i = 1; i <= n; i ++) {
		//std::cout << count[i] << ' ' << mp[i] << '\n';
		if (count[i] && mp[i] != 0) {
			std::cout << i << ' ';
		}
		mp[i] = 0;
	}	
	std::cout << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}