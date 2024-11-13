#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<array>
#include<set>
#include<map>
#include<utility>

using i64 = long long;
using namespace std;

template<typename T>
void take_max(T &a,const T &b) noexcept
{
    if(a<b)
        a=b;
}
template<typename T>
void take_max(T &a,T &&b) noexcept
{
    if(a<b)
        a=std::forward<T>(b);
}
template<typename T>
void take_min(T &a,const T &b) noexcept
{
    if(b<a)
        a=b;
}
template<typename T>
void take_min(T &a,T &&b) noexcept
{
    if(b<a)
        a=std::forward<T>(b);
}
template<typename T>
void print(T first,T last) noexcept
{
    if(first!=last)
    {
        do{
            (cout<<*first).put(' ');
        }while(++first!=last);
        cout.put('\n');
    }
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<uint,uint> PUU;
constexpr uint P_N=200005U,A_N=2000005U;
struct Node
{
    uint fail;
    uint ne[26U];
    uint ans_cnt;
};
uint idx;
Node tr[P_N];
void Trie_clear() noexcept
{
    idx=0U;
    memset(tr,0,sizeof(*tr));
}
char temp[P_N];
uint P_end[P_N];
void insert(const char *const s,const uint id) noexcept
{
    uint n(strlen(s));
    uint now(0U);
    for(uint i(0U);i!=n;++i)
    {
        if(tr[now].ne[s[i]-'a'])
        {
            now=tr[now].ne[s[i]-'a'];
        }
        else
        {
            ++idx;
            tr[now].ne[s[i]-'a']=idx;
            now=idx;
            memset(tr+idx,0,sizeof(*tr));
        }
    }
    P_end[id]=now;
}
class MyQueue
{
protected:
    uint head,tail;
    uint s[P_N];
public:
    void push(uint x) noexcept
    {
        s[tail++]=x;
    }
    void pop() noexcept
    {
        ++head;
    }
    uint &front() noexcept
    {
        return s[head];
    }
    bool not_empty() const noexcept
    {
        return head!=tail;
    }
    void get_fail_tree() const noexcept
    {
        for(uint i(tail-1U);~i;--i)
            tr[tr[s[i]].fail].ans_cnt+=tr[s[i]].ans_cnt;
    }
    void clear() noexcept
    {
        head=tail=0U;
    }
}qu;
void build() noexcept
{
    qu.clear();
    for(uint i(0U);i!=26U;++i)
        if(tr[0U].ne[i])
            qu.push(tr[0U].ne[i]);
    while(qu.not_empty())
    {
        const uint u(qu.front());
        qu.pop();
        for(uint i(0U);i!=26U;++i)
        {
            if(tr[u].ne[i])
            {
                tr[tr[u].ne[i]].fail=tr[tr[u].fail].ne[i];
                qu.push(tr[u].ne[i]);
            }
            else
                tr[u].ne[i]=tr[tr[u].fail].ne[i];
        }
    }
}
char A[A_N];
void ACsearch(const char *const s,const uint P_cnt) noexcept
{
    uint n(strlen(s));
    uint now(0U);
    for(uint i(0U);i!=n;++i)
    {
        now=tr[now].ne[s[i]-'a'];
        // cout<<now<<' ';
        ++tr[now].ans_cnt;
    }
    // cout.put('\n');
    // for(uint i(0U);i<=idx;++i)
    //     cout<<tr[i].ans_cnt<<' ';
    // cout.put('\n');
    qu.get_fail_tree();
    // for(uint i(0U);i<=idx;++i)
    //     cout<<tr[i].ans_cnt<<' ';
    // cout.put('\n');
    /*for(uint i(0U);i!=P_cnt;++i)
        cout<<tr[P_end[i]].ans_cnt<<'\n';*/
}

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
const int N = 2e6;
char s[N], x[N];
void solve() {
	int n;
	std::cin >> n;
	std::string t, y;
	std::cin >> s;
	std::cin >> t;
	auto p = kmp(t);
	int m = t.size();
	t = " " + t;
	
	Trie_clear();

	std::vector<int> count(n + 1);
	for (int i = 1; i <= n; i ++) {
		std::cin >> x;
		std::cin >> y;
		insert(x, i);
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
	build();
	//mp.clear();
	ACsearch(s, n + 1);
	for (int i = 1; i <= n; i ++) {
		//std::cout << count[i] << ' ' << mp[i] << '\n';
		if (count[i] && tr[P_end[i]].ans_cnt != 0) {
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