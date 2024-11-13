#include<cstdio>
#include<algorithm>
using namespace std;
int cp[8]={123,134,145,152,632,643,654,625};
int mp[10][13];
char s[13];
int t;
bool check(int a,int b,int c){
	int x,ans[3];
	if(a==1||a==6) x=a*100+b*10+c;
	if(b==1||b==6) x=b*100+c*10+a;
	if(c==1||c==6) x=c*100+a*10+b;
	for(int i=0;i<8;i++) if(x==cp[i]) return 1;
	ans[0]=a,ans[1]=b,ans[2]=c;
	sort(ans,ans+3);
	printf("%d %d %d\n",ans[0],ans[1],ans[2]);
	return 0;
}
int main(){
	scanf("%d",&t);
	while(t--){
		for(int i=1;i<=9;i++){
			scanf("%s",s+1);
			for(int j=1;j<=12;j++) mp[i][j]=s[j]-'0';
		}
		if( check(mp[3][4],mp[4][3],mp[4][4])&&
			check(mp[3][6],mp[4][6],mp[4][7])&&
			check(mp[1][6],mp[4][9],mp[4][10])&&
			check(mp[1][4],mp[4][12],mp[4][1])&&
			check(mp[7][4],mp[6][4],mp[6][3])&&
			check(mp[7][6],mp[6][7],mp[6][6])&&
			check(mp[9][6],mp[6][10],mp[6][9])&&
			check(mp[9][4],mp[6][1],mp[6][12])
			){
			printf("No problem\n");
		}
	}
	return 0;
}