//#pragma GCC optimize(2)
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<map>
using namespace std;
#define re register
using i64 = long long;
#define endl "\n"
#define lc(x) T[x].lc
#define rc(x) T[x].rc
#define pii pair<int,int>
#define p1(x) (x).first
#define p2(x) (x).second
struct node{
    int mp[26];
	int f,fa,res,cnt;	
}T[200300];
int cnt;
inline int g(int x,char c){
	if(!T[x].mp[c-'a'])T[x].mp[c-'a']=++cnt,T[cnt].fa=x;
	return T[x].mp[c-'a'];
}
int loc[200300];
inline int ins(string t){
	int now=0;
	for(char x:t)
	now=g(now,x);
	return now;
}
int n;
inline void bd(){
	queue<int>q;
	q.push(0);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(char i='a';i<='z';i++)
			if(!T[u].mp[i-'a'])T[u].mp[i-'a']=T[T[u].f].mp[i-'a'];
			else q.push(T[u].mp[i-'a']),T[T[u].mp[i-'a']].f=u?T[T[u].f].mp[i-'a']:0;
	}	
}

inline void add(string s){
	int now=0;
	for(char x:s)
	now=T[now].mp[x-'a'],T[now].cnt++;
}
int ct[203000];
inline void flush(){
	queue<int>q;
	for(int i=1;i<=cnt;i++)
		 ct[T[i].f]++;
	for(int i=0;i<=cnt;i++)
		if(!ct[i])q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		T[T[u].f].cnt+=T[u].cnt;
		if(!(--ct[T[u].f]))
			q.push(T[u].f);
	}
	for(int i=1;i<=cnt;i++)
	T[i].res+=T[i].cnt,T[i].cnt=0;
}

std::vector<int> kmp(std::string s) {
	int n = s.size();
	std::vector<int> f(n + 1);
	for (re int i = 1, j = 0; i < n; i ++) {
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
	
	std::vector<int> count(n + 1);
	for (re int i = 1; i <= n; i ++) {
		std::cin >> x >> y;
		loc[i] = ins(x);
		int z = y.size();
		y = " " + y;
		bool f = 0;
		for (re int i = 1, j = 0; i <= z; i ++) {
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
	bd();
	add(s);
	flush();
	for (re int i = 1; i <= n; i ++) {
		//std::cout << count[i] << ' ' << mp[i] << '\n';
		if (count[i] && T[loc[i]].res != 0) {
			std::cout << i << ' ';
		}
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