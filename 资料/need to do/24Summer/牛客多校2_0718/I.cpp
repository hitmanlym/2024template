#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define MAXN 6005
using namespace std;
 
int n;
int a[MAXN],c[MAXN];
int f[MAXN],s[MAXN];
int p1[MAXN],p2[MAXN];
 
struct node{
    int l,r,len,id;
    friend bool operator < (node a,node b){
        return a.len<b.len;
    }
} b[MAXN];
int ans[MAXN];
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++){
        scanf("%d",&a[i]);
        if(!b[a[i]].l) b[a[i]].l=i;
        else b[a[i]].r=i;
    }
 
    // for(int i=1;i<=n;i++)
    //  printf("%d %d %d\n",i,b[i].l,b[i].r);
    // printf("\n");
 
    for(int i=1;i<=n;i++){
        b[i].len=b[i].r-b[i].l+1;
        b[i].id=i;
        p1[i]=b[i].l,p2[i]=b[i].r;
    }
 
 
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++){
        int x=b[i].id,l=b[i].l+1,r=b[i].r-1,len=b[i].len;
        for(int j=l;j<=r;j++){
            if(a[j]>x) c[j]=a[j];
            else c[j]=0;
        }
        memset(f,0,sizeof(f));
        memset(s,0,sizeof(s));
 
        // printf("x=%d\n",x);
        // printf("l=%d r=%d len=%d\n",l,r,len);
        // for(int j=l;j<=r;j++)
        //  printf("%d ",c[j]);
        // printf("\n");
 
        for(int j=l;j<=r;j++){
            int y=c[j];
            if(y && j==p2[y] && p1[y]>=l){
                int v1=f[j-1] + x;
                int v2=f[p1[y]-1] + ans[y];
                if(v1>=v2){
                    f[j]= v1;
                } else {
                    f[j] = v2;
                }
            } else
                f[j] = f[j - 1] + x;
        }
        ans[x]=f[r];
 
        // for(int j=l;j<=r;j++)
        //  printf("%d ",f[j]);
        // printf("\n");
        // for(int j=l;j<=r;j++)
        //  printf("%d ",s[j]);
        // printf("\n");
        // printf("%d\n",ans[x]);
 
    }
    // for(int i=1;i<=n;i++)
    //  printf("%d ",ans[i]);
    // printf("\n");
    memset(f,0,sizeof(f));
    for(int i=1;i<=2*n;i++){
        f[i]=f[i-1];
        int y=a[i];
        if(i==p2[y]) f[i]=max(f[i],f[p1[y]-1]+ans[y]);
    }
    printf("%d\n",f[2*n]);
    return 0;
}
