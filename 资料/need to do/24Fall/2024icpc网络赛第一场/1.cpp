#include<cstdio>
int a[40],n,t;
int main(){
	scanf("%d",&t);
	while(t--){
		n=0;
		for(int i=1;i<=32;i++){
			scanf("%d",&a[i]);
			if(a[i]<a[1]) n++;
		}
		if(n>=31) printf("1\n");
		else if(n>=27) printf("2\n");
		else if(n>=13) printf("4\n");
		else if(n>=6) printf("8\n");
		else if(n>=2) printf("16\n");
		else printf("32\n");
	}
	return 0;
}