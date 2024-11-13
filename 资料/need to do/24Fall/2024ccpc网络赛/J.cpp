#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define MAXN 1000010

int n;
int a[MAXN],b[MAXN],c[MAXN];
int p[40];

void insert(int x){
	for(int i=30;i>=0;i--){
		int c=x>>i&1;
		if(c){
			if(!p[i]){
				p[i]=x;
				return;
			}else x^=p[i];
		}
	}
}
void change(){
	for(int i=0;i<=30;i++){
		for(int j=i+1;j<=30;j++)
			p[j]^=p[i];
	}
}

void solve(){
	memset(p,0,sizeof(p));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	int A=0,B=0;
	for(int i=1;i<=n;i++){
		A^=a[i];
		B^=b[i];
		c[i]=a[i]^b[i];
		insert(c[i]);
	}
	change();
	int id=-1;
	for(int i=30;i>=0;i--){
		int x=A>>i&1,y=B>>i&1;
		if(!x && !y) continue;
		if(x && y){
			A^=p[i];
			B^=p[i];
		}
		else if(id==1 && x){
			A^=p[i];
			B^=p[i];
		}
		else if(id==2 && y){
			A^=p[i];
			B^=p[i];
		}
		if(id==-1){
			if(x && !y) id = 1;
			if(!x && y) id = 2;
		}
	}
	printf("%d\n",max(A,B));
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}