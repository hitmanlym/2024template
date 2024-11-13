#include<cstdio>
#include<queue>
using namespace std;
#define MAXN 2010

int n;
int a[MAXN];
int b[MAXN][MAXN],c[MAXN][MAXN];
priority_queue<int> q;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int l=1;l<=n;l++){
		for(int r=l;r<=n;r++){
			while(!q.empty()) q.pop();
			for(int i=l;i<=r;i++)
				q.push(a[i]);
			int len=r-l+1;
			int cnt=len-(len+1)/2;
			while(cnt){
				q.pop();
				cnt--;
			}
			b[l][r]=q.top();
		}
	}
	for(int l=1;l<=n;l++){
		for(int r=l;r<=n;r++){
			while(!q.empty()) q.pop();
			int len=0;
			for(int i=l;i<=r;i++)
				for(int j=i;j<=r;j++){
					q.push(b[i][j]);
					len++;
				}
			int cnt=len-(len+1)/2;
			while(cnt){
				q.pop();
				cnt--;
			}
			c[l][r]=q.top();
		}
	}
	while(!q.empty()) q.pop();
	int len=0;
	for(int l=1;l<=n;l++)
		for(int r=l;r<=n;r++){
			len++;
			q.push(c[l][r]);
		}
	int cnt=len-(len+1)/2;
	while(cnt){
		q.pop();
		cnt--;
	}
	printf("%d\n",q.top());
	return 0;
}