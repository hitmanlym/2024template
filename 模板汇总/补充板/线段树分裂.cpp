#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=200010;
int n,m,tot,cnt,seq=1,op,x,y,z,bac[MAXN<<5],ch[MAXN<<5][2],rt[MAXN];
ll val[MAXN<<5];
int newnod () {return (cnt?bac[cnt--]:++tot);}
void del (int p) {
	bac[++cnt]=p,ch[p][0]=ch[p][1]=val[p]=0;
	return;
}
void modify (int &p,int l,int r,int pos,int v) {
	if (!p) {p=newnod();}
	val[p]+=v;
	if (l==r) {return;}
	int mid=(l+r)>>1;
	if (pos<=mid) {modify(ch[p][0],l,mid,pos,v);}
	else {modify(ch[p][1],mid+1,r,pos,v);}
	return;
}
ll query (int p,int l,int r,int xl,int xr) {
	if (xr<l||r<xl) {return 0;}
	if (xl<=l&&r<=xr) {return val[p];}
	int mid=(l+r)>>1;
	return query(ch[p][0],l,mid,xl,xr)+query(ch[p][1],mid+1,r,xl,xr);
}
int kth (int p,int l,int r,int k) {
	if (l==r) {return l;}
	int mid=(l+r)>>1;
	if (val[ch[p][0]]>=k) {return kth(ch[p][0],l,mid,k);}
	else {return kth(ch[p][1],mid+1,r,k-val[ch[p][0]]);}
}
int merge (int x,int y) {
	if (!x||!y) {return x+y;}
	val[x]+=val[y];
	ch[x][0]=merge(ch[x][0],ch[y][0]);
	ch[x][1]=merge(ch[x][1],ch[y][1]);
	del(y); 
	return x;
}
void split (int x,int &y,ll k) { // 分裂出 x 为原 x 的前 k 个
	if (x==0) {return;}
	y=newnod();
	ll v=val[ch[x][0]];
	if (k>v) {split(ch[x][1],ch[y][1],k-v);}
	else {swap(ch[x][1],ch[y][1]);}
	if (k<v) {split(ch[x][0],ch[y][0],k);}
	val[y]=val[x]-k;
	val[x]=k;
	return;
}
int main () {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d",&x);
		modify(rt[1],1,n,i,x);
	}
	for (int i=1;i<=m;i++) {
		scanf("%d",&op);
		if (op==0) {
			scanf("%d%d%d",&x,&y,&z);
			ll k1=query(rt[x],1,n,1,z),k2=query(rt[x],1,n,y,z);
			int tmp=0;
			split(rt[x],rt[++seq],k1-k2);
			split(rt[seq],tmp,k2);
			rt[x]=merge(rt[x],tmp);
		} else if (op==1) {
			scanf("%d%d",&x,&y);
			rt[x]=merge(rt[x],rt[y]);
		} else if (op==2) {
			scanf("%d%d%d",&x,&y,&z);
			modify(rt[x],1,n,z,y);
		} else if (op==3) {
			scanf("%d%d%d",&x,&y,&z);
			printf("%lld\n",query(rt[x],1,n,y,z));
		} else if (op==4) {
			scanf("%d%d",&x,&y);
			if (val[rt[x]]<y) {printf("-1\n");continue;}
			printf("%d\n",kth(rt[x],1,n,y));
		}
	}
	return 0;
}