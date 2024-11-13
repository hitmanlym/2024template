#include<cstdio>
#include<cstring>
using namespace std;
#define MAXN 1000010

int n;
char s[MAXN];
void solve(){
	scanf("%s",s+1);
	int cnt=0;
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='(') cnt++;
		if(s[i]==')'){
			cnt--;
			if(cnt<0) cnt=0;
		}
	}
	if(cnt)
		puts("impossible");
	else printf("%s\n",s+1);
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}