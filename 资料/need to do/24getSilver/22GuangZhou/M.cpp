#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

const int mo=1000000007;
ll n,k;
int m,cm,cn;
int bm[64],bn[64];
int C[20][20];
int f[50][1<<8][20][2];

int getn(int l,int r){
	l--,r--;
	return n>>l&((1ll<<(r-l+1))-1); 
}
int main()
{
	scanf("%lld%lld%d",&n,&m,&k);
	// printf("%d\n",getn(1,3));

	C[0][0]=1;
	for(int i=1;i<=k;i++){
		C[i][0]=1;
		for(int j=1;j<=k;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mo;
	}

	while(m){
		bm[++cm]=m&1ll;
		m>>=1ll;
	}
	ll n1=n;
	while(n1){
		bn[++cn]=n1&1ll;
		// printf("! %d\n",n1&1ll);
		n1>>=1ll;
		// printf("!! %d\n",n1);
	}
	memset(f,0,sizeof(f));
	f[cm+1][0][k][0]=1;

	for(int i=cm+1;i>1;i--){
		for(int j=0;j<(1<<8);j++){
			for(int t=0;t<=k;t++){
				// if(i==2 && j==0 && t==0)
				// 	printf("?\n");
				if(!f[i][j][t][0] && !f[i][j][t][1]) continue;
				// if(i==2 && j==0 && t==0)
				// 	printf("?\n");
				if(bm[i-1]==0){
					for(int d=0;d<=k-t;d++){
						int s=d*(k-d);
						int s1=((j<<1)+s);
						int p=s1&127, q=s1>>8, c=s1>>9;
						ll v1=1ll*f[i][j][t][1]*C[k-t][d]%mo, v0=1ll*f[i][j][t][0]*C[k-t][d]%mo;
						if(p>getn(i-1,i+6)){
							if(c==0 && q==1)
								f[i-1][p][t][1]=(f[i-1][p][t][1]+v1)%mo;
						}else {
							if(c==1){
								if(q<=bn[i+7]){
									if(q==0 && bn[i+7]==1) f[i-1][p][t][1]=(f[i-1][p][t][1]+v1)%mo;
									else f[i-1][p][t][0]=(f[i-1][p][t][0]+v1)%mo;
								}
							}else {
								if(q==1 && bn[i+7]==0) f[i-1][p][t][1]=(f[i-1][p][t][1]+v1)%mo;
								else if(q==0 && bn[i+7]==1) f[i-1][p][t][1]=(f[i-1][p][t][1]+v0)%mo;
								else f[i-1][p][t][0]=(f[i-1][p][t][0]+v0)%mo; 
							}
						}
					}
				}else {
					for(int d=0;d<=k;d++){
						int s=d*(k-d);
						int s1=((j<<1)+s);
						int p=s1&127, q=s1>>8, c=s1>>9;
						// if(q==1 || c==1)
						// 	printf("error\n");
						for(int e=0;e<=min(d,t);e++){
							ll v0=1ll*f[i][j][t][0]*C[t][e]%mo*C[k-t][d-e]%mo;
							ll v1=1ll*f[i][j][t][1]*C[t][e]%mo*C[k-t][d-e]%mo;
							// if(t==0 && e==0 && i==2 && j==0){
							// 	printf("!! s1=%d p=%d q=%d c=%d\n",s1,p,q,c);
							// }
							if(p>getn(i-1,i+6)){
								if(c==0 && q==1)
									f[i-1][p][e][1]=(f[i-1][p][e][1]+v1)%mo;
							}else {
								if(c==1){
									if(q<=bn[i+7]){
										if(q==0 && bn[i+7]==1) f[i-1][p][e][1]=(f[i-1][p][e][1]+v1)%mo;
										else f[i-1][p][e][0]=(f[i-1][p][e][0]+v1)%mo;
									}
								}else {
									if(q==1 && bn[i+7]==0) f[i-1][p][e][1]=(f[i-1][p][e][1]+v1)%mo;
									else if(q==0 && bn[i+7]==1) f[i-1][p][e][1]=(f[i-1][p][e][1]+v0)%mo;
									else f[i-1][p][e][0]=(f[i-1][p][e][0]+v0)%mo; 
								}
							}
						}
					}
				}
			}
		}
	}

	// printf("\n");
	// for(int i=cm;i>=1;i--)
	// 	printf("%d",bm[i]);
	// printf("\n");

	// printf("\n");
	// for(int i=cn;i>=1;i--)
	// 	printf("%d",bn[i]);
	// printf("\n");

	// for(int i=cm;i>=1;i--)
	// 	for(int j=0;j<(1<<7);j++)
	// 		for(int t=0;t<=k;t++){
	// 			if(f[i][j][t][0])
	// 				printf("f[%d][%d][%d][0]=%d\n",i,j,t,f[i][j][t][0]);
	// 			if(f[i][j][t][1])
	// 				printf("f[%d][%d][%d][1]=%d\n",i,j,t,f[i][j][t][1]);
	// 		}
	ll ans=0;
	for(int t=0;t<=k;t++)
		ans=(ans+f[1][getn(1,8)][t][0])%mo;
	printf("%lld\n",ans);
	return 0;
}