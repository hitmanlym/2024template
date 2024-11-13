#include<cstdio> 
#include<cstring>
#include<map>
using namespace std;
#define ull unsigned long long

ull const bas = 13131;
int n,m;
char s[10010];
map <ull,bool> mp;

bool check(){
	for(int i=1;i<=strlen(s+1)-2;i++){
		if(s[i]=='b' && s[i+1]=='i' && s[i+2]=='e') return true;
	}
	return false;
}

int main()
{
	scanf("%d",&n);
	bool flag=false;
	for(int i=1;i<=n;i++){
		scanf("%d",&m);
		flag=false;
		for(int j=1;j<=m;j++){
			scanf("%s",s+1);
			ull nowhas=0;
			for(int k=1;k<=strlen(s+1);k++)
				nowhas=nowhas*bas+s[k];
			if(check() && !mp[nowhas]){
				printf("%s\n",s+1);
				mp[nowhas]=true;
				flag=true;
			}
		}
		if(!flag)
			printf("Time to play Genshin Impact, Teacher Rice!\n");
	}
	return 0;
}