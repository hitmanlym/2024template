#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
const ll mo=998244353;

struct Matrix{
	ll v[4][4];
	friend Matrix operator * (Matrix a, Matrix b){
		Matrix c;
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++){
				c.v[i][j]=0;
				for(int k=1;k<=3;k++)
					c.v[i][j]=(c.v[i][j]+a.v[i][k]*b.v[k][j]%mo)%mo;
			}
		return c;
	}
} I;
Matrix qmi(Matrix x,ll y){
	Matrix ans=I;
	// for(int i=1;i<=3;i++){
	// 	for(int j=1;j<=3;j++)
	// 		printf("%lld ",ans.v[i][j]);
	// 	printf("\n");
	// }
	while(y){
		if(y&1ll){
			ans=ans*x;

			// for(int i=1;i<=3;i++){
			// 	for(int j=1;j<=3;j++)
			// 		printf("%lld ",ans.v[i][j]);
			// 	printf("\n");
			// }
		}
		y>>=1ll;
		x=x*x;
	}
	return ans;
}
ll gcd(ll a,ll b){ return b==0?a:gcd(b,a%b); }

void solve()
{
	ll A,B;
	scanf("%lld%lld",&A,&B);
	ll g=gcd(A,B);
	A/=g,B/=g;
	if(A<=B){
		ll x=B/A, y=B%A;
		Matrix F1, F2;
		F1.v[1][1]=F1.v[2][1]=F1.v[3][1]=1;
		F1.v[1][2]=x,F1.v[2][2]=x+1,F1.v[3][2]=2*x;
		F1.v[1][3]=F1.v[2][3]=0,F1.v[3][3]=1;

		// printf("F1:\n");
		// for(int i=1;i<=3;i++){
		// 	for(int j=1;j<=3;j++)
		// 		printf("%lld ",F1.v[i][j]);
		// 	printf("\n");
		// }
		// printf("\n");

		F2.v[1][1]=F2.v[2][1]=F2.v[3][1]=1;
		F2.v[1][2]=x+1,F2.v[2][2]=x+2,F2.v[3][2]=2*x+2;
		F2.v[1][3]=F2.v[2][3]=0,F2.v[3][3]=1;

		printf("x=%lld y=%lld\n",x,y);

		if(y==0){
			Matrix ans = qmi(F1,A);

			// printf("ans:\n");
			// for(int i=1;i<=3;i++){
			// 	for(int j=1;j<=3;j++)
			// 		printf("%lld ",ans.v[i][j]);
			// 	printf("\n");
			// }
			// printf("\n");
			ans=qmi(ans,g);
			printf("%lld\n",(ans.v[3][1]+ans.v[3][2]+1)%mo);
		}else if(y<=A/2){
			// printf("!\n");
			Matrix G1,G2;
			// printf("!\n");
			G1=F2*qmi(F1,A/y-1);
			// printf("!\n");
			G2=F2*qmi(F1,A/y);
			// printf("!\n");
			Matrix ans = qmi(G1,y-A%y) * qmi(G2,A%y);
			// printf("!\n");
			ans=qmi(ans,g);
			printf("%lld\n",(ans.v[3][1]+ans.v[3][2]+1)%mo);
		}else {
			// printf("!\n");
			y=A-y;
			Matrix G1,G2;
			G1=qmi(F2,A/y)*F1;
			// printf("!\n");
			G2=qmi(F2,A/y-1)*F1;
			// printf("!\n");
			Matrix ans = qmi(G1,A%y) * qmi(G2,y-A%y);
			// printf("!\n");
			ans=qmi(ans,g);
			printf("%lld\n",(ans.v[3][1]+ans.v[3][2]+1)%mo);
		}
	}else {
		A--;
		ll x=A/B, y=A%B;
		// printf("x=%lld y=%lld\n",x,y);
		Matrix F1, F2;
		F1.v[1][1]=x+1,F1.v[2][1]=x,F1.v[3][1]=2*x;
		F1.v[1][2]=F1.v[2][2]=F1.v[3][2]=1;
		F1.v[1][3]=F1.v[2][3]=0,F1.v[3][3]=1;


		// printf("F1:\n");
		// for(int i=1;i<=3;i++){
		// 	for(int j=1;j<=3;j++)
		// 		printf("%lld ",F1.v[i][j]);
		// 	printf("\n");
		// }
		// printf("\n");


		F2.v[1][1]=x+2,F2.v[2][1]=x+1,F2.v[3][1]=2*x+2;
		F2.v[1][2]=F2.v[2][2]=F2.v[3][2]=1;
		F2.v[1][3]=F2.v[2][3]=0,F2.v[3][3]=1;


		// printf("F2:\n");
		// for(int i=1;i<=3;i++){
		// 	for(int j=1;j<=3;j++)
		// 		printf("%lld ",F2.v[i][j]);
		// 	printf("\n");
		// }
		// printf("\n");

		if(y==0){
			Matrix ans = qmi(F1,B);
			Matrix now = I;
			now.v[2][1]=now.v[3][1]=1;
			ans=qmi(ans*now ,g-1)*ans;
			printf("%lld\n",(ans.v[1][1]+ans.v[1][2]+ans.v[1][3]+ans.v[3][1]+ans.v[3][2]+1)%mo);
		}else if(y<=B/2){
			ll p=(B-y)/(y+1),q=(B-y)%(y+1);
			// printf("%lld %lld\n",p,q);
			Matrix G1,G2;
			G1=qmi(F1,p+1)*F2;
			G2=qmi(F1,p)*F2;

			// printf("G2:\n");
			// for(int i=1;i<=3;i++){
			// 	for(int j=1;j<=3;j++)
			// 		printf("%lld ",G2.v[i][j]);
			// 	printf("\n");
			// }
			// printf("\n");

			Matrix ans;
			if(q){
				ans = qmi(G1, q/2) * qmi(G2, y+1-q) ;
				ans = ans * qmi(G1, q/2-1) ;
				ans = ans * qmi(F1, p+1);
			}else {
				// printf("!\n");
				Matrix now = qmi(F1, p);

				// printf("now:\n");
				// for(int i=1;i<=3;i++){
				// 	for(int j=1;j<=3;j++)
				// 		printf("%lld ",now.v[i][j]);
				// 	printf("\n");
				// }
				// printf("\n");

				ans = qmi(G2, y) * now;
			}
			Matrix now = I;
			now.v[2][1]=now.v[3][1]=1;
			ans=qmi(ans*now ,g-1)*ans;
			printf("%lld\n",(ans.v[1][1]+ans.v[1][2]+ans.v[1][3]+ans.v[3][1]+ans.v[3][2]+1)%mo);
		}else {
			ll z=B-y;
			ll p=y/(z-1),q=y%(z-1);
			Matrix G1,G2;
			G1=F1*qmi(F2,p+1);
			G2=F1*qmi(F2,p);
			Matrix ans;
			if(q){
				ans = qmi(G1, q/2) * qmi(G2, z+1-q) * F1;
				ans = ans * qmi(G1, q/2-1) ;
			}else {
				ans = qmi(G2, z-q) * F1;
			}
			Matrix now = I;
			now.v[2][1]=now.v[3][1]=1;
			ans=qmi(ans*now ,g-1)*ans;
			printf("%lld\n",(ans.v[1][1]+ans.v[1][2]+ans.v[1][3]+ans.v[3][1]+ans.v[3][2]+1)%mo);
		}
	}
}

int main()
{
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			I.v[i][j]=0;
	for(int i=1;i<=3;i++)
		I.v[i][i]=1;
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}