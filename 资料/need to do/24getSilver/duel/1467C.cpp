#include<bits/stdc++.h>
#define int long long
using namespace std;
int n1,n2,n3,m1,m2,m3,s1,s2,s3;
int a[300005],b[300005],c[300005];
signed main()
{
	cin>>n1>>n2>>n3;
	m1=m2=m3=0x3f3f3f3f;
	
	for(int i=1;i<=n1;i++) scanf("%lld",&a[i]),m1=min(m1,a[i]),s1+=a[i];
	for(int i=1;i<=n2;i++) scanf("%lld",&b[i]),m2=min(m2,b[i]),s2+=b[i];
	for(int i=1;i<=n3;i++) scanf("%lld",&c[i]),m3=min(m3,c[i]),s3+=c[i];
	int ans=0;
	ans=max(ans,s2+s3-s1);
	ans=max(ans,s1+s3-s2);
	ans=max(ans,s1+s2-s3);
	ans=max(ans,s1+s2+s3-2*min(m1+m2,min(m1+m3,m2+m3)));
	cout<<ans;
	return 0;
}