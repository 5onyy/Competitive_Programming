#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#define fr(a,b,c) for (a=b;a<=c;a++)
#define N 200200
using namespace std;

int n,m,h[N],p[N],re,lab[N];
vector < int > a[N];

void init(int x)
{
    int i,y;
    fr(i,0,int(a[x].size())-1)
    {
        y=a[x][i];
        if (y==p[x]) continue;
        h[y]=h[x]+1; p[y]=x;
        init(y);
    }
}

int get(int x)
{
    if (lab[x]!=x) lab[x]=get(lab[x]);
    return lab[x];
}

void go(int X,int Y)
{
    int x=X,y=Y;
    while (x!=y)
    {
        x=get(x); y=get(y);
        if (x==y) break;
        int hx=h[x], hy=h[y];
        if (hx<=hy) y=lab[y]=p[y], re--;
        if (hy<=hx) x=lab[x]=p[x], re--;
    }
}

int main()
{
    int i,x,y;
    cin >> n;
    fr(i,2,n)
    {
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    init(1);
    re=n-1;
    fr(i,1,n) lab[i]=i;
    cin >> m;
    fr(i,1,m) 
    {
        scanf("%d%d",&x,&y);
        go(x,y);
    }
    cout << re << endl;
    return 0;
}
