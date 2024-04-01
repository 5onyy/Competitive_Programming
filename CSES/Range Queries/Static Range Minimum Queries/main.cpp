#include<bits/stdc++.h>

using namespace std;

#define fastIO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define fi first
#define se second
#define pb push_back
#define pf push_front
#define mp make_pair
#define inf 999999999
#define sz(x) (int)(x).size()
#define int long long
#define double long double
#define log2i(x) (64 - __builtin_clzll(1ll * (x)) - 1)
#define hardio(x)      freopen(x".inp","r",stdin), freopen(x".out","w",stdout);
#define all(x)         x.begin(),x.end()
#define rall(x)        x.rbegin(),x.rend()

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int maxN=2*1e5+1;
const int BASE=311;
const int N=1e5+5;
const int MOD=1000000003;
const int d4i[4]={-1, 0, 1, 0}, d4j[4]={0, 1, 0, -1};
const int d8i[8]={-1, -1, 0, 1, 1, 1, 0, -1}, d8j[8]={0, 1, 1, 1, 0, -1, -1, -1};

int n,q;
int LG=log2i(maxN);
int a[maxN];
vector<vi> st(maxN,vi(LG+1));

void buildRMQ()
{
    for (int i=1;i<=n;i++)  st[i][0]=a[i];
    for (int j=1;j<=LG;j++)
    {
        for (int i=1;i+(1<<j)-1<=n;i++)
        {
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}

int getmin(int l,int r)
{
    int k=log2i(r-l+1);
    return min(st[l][k],st[r-(1<<k)+1][k]);
}

signed main()
{
    //hardio("t");
    fastIO;
    cin>>n>>q;
    for (int i=1;i<=n;i++)
        cin>>a[i];
    buildRMQ();
    while (q--)
    {
        int u,v;
        cin>>u>>v;
        cout<<getmin(u,v)<<endl;
    }
}
