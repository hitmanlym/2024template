#include<bits/stdc++.h>
using i64 = long long;

//int O;
//std::map<int, int> mp;
struct AhoCorasick {
    int CNT;
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        int end; // val // 以之结尾的单词数
        std::vector<int> st;
        std::array<int, ALPHABET> next;
        Node() : link{}, next{} {}
    };
    
    std::vector<Node> t;
    
    AhoCorasick() {
        init();
    }
    
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        //t[0].len = -1;
        t[1].next.fill(0);
        //t[1].len = -1;
        t[1].end = 0;
        //t[1].st.clear();
    }
    
    int newNode() {
        t.emplace_back();
        CNT = t.size() - 1;
        t[CNT].next.fill(0);
        t[CNT].end = 0;
        //t[CNT].st.clear();
        return CNT;
    }
    
    int add(const std::vector<int> &a) {
        int p = 1;
        for (auto x : a) {
            if (t[p].next[x] == 0) {
                int rev = newNode();
                t[p].next[x] = rev;
                //t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        //t[p].st.push_back(O);
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
            for (int now = p; now/* && t[now].end != -1 */; now = t[now].link) {
                // something.
                t[now].end = -1;
            }
            //t[p].end ++;
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


void solve() {
    AhoCorasick t;
    int n;
    std::cin >> n;
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i ++) {
        std::cin >> s[i];
        O = i;
        t.add(s[i]);
    }
    t.work();
    mp.clear();
    std::string T;
    std::cin >> T;
    t.query(T);
    t.LinkTree();
    for (int i = 0; i < n; i ++) {
        std::cout << mp[i] << '\n';
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin >> t;
    while (t --) {
        solve();
    }
    return 0;
}