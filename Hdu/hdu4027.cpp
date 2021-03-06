#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=100010;

typedef long long LL;

LL A[maxm],tr[maxm<<2],left[maxm<<2],right[maxm<<2];
int test;

int build(int id,int l,int r){
    left[id]=l;right[id]=r;
    if(l==r)return tr[id]=A[l],0;
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
    tr[id]=tr[id<<1]+tr[id<<1|1];
}

void modify(int id,int l,int r){
    if(left[id]==right[id]&&left[id]>=l&&right[id]<=r){
		tr[id]=sqrt(1.0*tr[id]);
		return;
    }

    if(left[id]>=l&&right[id]<=r&&tr[id]==right[id]-left[id]+1)return;
    if(left[id]>r||right[id]<l)return;
    modify(id<<1,l,r);
    modify(id<<1|1,l,r);
    tr[id]=tr[id<<1]+tr[id<<1|1];
}

LL Query(int id,int l,int r){
    if(left[id]>=l&&right[id]<=r)return tr[id];
    if(left[id]>r||right[id]<l)return 0;
    return (Query(id<<1,l,r)+Query(id<<1|1,l,r));
}

int main(){
    int n,m,opt,l,r,x,y;
    while(scanf("%d", &n)!=EOF){
		memset(A,0,sizeof A);
		memset(tr,0,sizeof tr);
		for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
		build(1,1,n);
        scanf("%d", &m);
        printf("Case #%d:\n", ++test);
        while(m--){
            scanf("%d%d%d", &opt, &x, &y);
            l=min(x,y);
            r=max(x,y);
            if(opt==0) modify(1,l,r);
            else printf("%lld\n",Query(1,l,r));
        }
        puts("");
    }
    
    
    return 0;
}
