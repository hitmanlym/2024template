#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
#define ll long long

int n;
int d[4][3];
vector<ll> t;

int main()
{
	scanf("%d",&n);
	char s[2];
	memset(d,-0x3f,sizeof(d));
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d%s",&x,&y,s);
		if(s[0]=='E'){
			d[2][0]=max(d[2][0],y);
			d[3][0]=max(d[3][0],-y);
			d[0][1]=max(d[0][1],x);
			d[1][2]=max(d[1][2],-x);
		}
		if(s[0]=='W'){
			d[2][0]=max(d[2][0],y);
			d[3][0]=max(d[3][0],-y);
			d[0][2]=max(d[0][2],x);
			d[1][1]=max(d[1][1],-x);
		}
		if(s[0]=='S'){
			d[0][0]=max(d[0][0],x);
			d[1][0]=max(d[1][0],-x);
			d[2][2]=max(d[2][2],y);
			d[3][1]=max(d[3][1],-y);
		}
		if(s[0]=='N'){
			d[0][0]=max(d[0][0],x);
			d[1][0]=max(d[1][0],-x);
			d[2][1]=max(d[2][1],y);
			d[3][2]=max(d[3][2],-y);
		}
	}
	for(int i=0;i<4;i++){
		int t2=(d[i][2]-d[i][1]);
		double x=t2/2;
		if(x<=d[i][0]){
			t.push_back(t2/2);
		}else {
			t.push_back(d[i][0]-d[i][1]);
			t.push_back(d[i][2]-d[i][0]);
		}
		for(int j=i+1;j<4;j++){
			t.push_back(d[i][0]-d[j][1]);
			t.push_back(d[j][2]-d[i][0]);
			t.push_back(d[j][0]-d[i][1]);
			t.push_back(d[i][2]-d[j][0]);
			t.push_back((d[j][2]-d[i][1])/2);
			t.push_back((d[i][2]-d[j][1])/2);
		}
	}
	t.push_back(0);
	t.push_back(2e9);
	sort(t.begin(),t.end());
	int now=0;
	ll ans=1e18;
	while(now<t.size() && t[now]<0) now++;
	while(now<t.size()){
		for(int x=-5;x<=5;x++){
			int nt=t[now]+x;
			if(nt<0) continue;
			ll nowans=0;
			for(int i=0;i<4;i++)
				nowans+=max(d[i][0],max(d[i][1]+nt,d[i][2]-nt));
			ans=min(ans,2*nowans);
		}
		now++;
	}
	printf("%lld\n",ans);
}

/*
5
0 2000 E
0 6000 S
2000 0 N
2000 6000 S
4000 4000 W
*/