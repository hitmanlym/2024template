#include<cstdio>
#include<queue>
using namespace std;
struct E{
	int to,nxt,c;
}e[10005];
struct node{
	int num,d,en;
	friend bool operator < (node x,node y){
		if(x.d==y.d) return x.num>y.num;
		return x.d<y.d;
	}
};
priority_queue<node> q1,q2;
int n,m,k,t,cnt,d[1005],hd[1005],c1[1005],c2[1005],tp1,tp2,ccnt;
bool f,b[1005],fl;
void EE(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=hd[u];
	e[cnt].c=0;
	hd[u]=cnt;
	d[v]++;
	return;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&k),cnt=-1,ccnt=f=0;
		while(!q1.empty()) q1.pop();
		while(!q2.empty()) q2.pop();
		for(int i=1;i<=n;i++) hd[i]=-1,d[i]=b[i]=0;
		for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),EE(u,v),EE(v,u);
		for(int i=1;i<=n;i++) q1.push(node{i,d[i],0});
		while(!q1.empty()){
			int u=q1.top().num,v,en,cl;q1.pop(),tp1=tp2=fl=0;
			for(int i=hd[u];i!=-1;i=e[i].nxt) v=e[i].to,q2.push(node{v,d[v],i});
			while(!q2.empty()){
				v=q2.top().num,en=q2.top().en,cl=e[en].c,q2.pop();
				if(!fl){
					if(cl) c1[++tp1]=cl;
					else e[en].c=e[en^1].c=++ccnt,c2[++tp2]=ccnt;
					if(tp1+tp2==k) fl=1;
				}
				else{
					if(cl){
						f=1;
						break;
					}
					while(tp1&&b[c1[tp1]]) tp1--;
					if(tp1) e[en].c=e[en^1].c=c1[tp1],b[c1[tp1--]]=1;
					else if(!tp2){
						f=1;
						break;
					}
					else e[en].c=e[en^1].c=c2[tp2],b[c2[tp2--]]=1;
				}
			}
			if(f) break;
		}
		if(f){
			for(int i=1;i<=m;i++) printf("0 ");
			printf("\n");
		}
		else{
			for(int i=0;i<2*m;i+=2) printf("%d ",e[i].c);
			printf("\n");	
		}
	}
}