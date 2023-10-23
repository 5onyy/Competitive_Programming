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

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> ii;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ii> vii;

const ll BASE=311;
const ll MOD=1000000003;
const int d4i[4]={-1, 0, 1, 0}, d4j[4]={0, 1, 0, -1};
const int d8i[8]={-1, -1, 0, 1, 1, 1, 0, -1}, d8j[8]={0, 1, 1, 1, 0, -1, -1, -1};

int n,m;
multiset<int> a;

int main()
{
//    freopen(".INP","r",stdin);
//    freopen(".OUT","w",stdout);
    fastIO;
    cin>>n>>m;
    for (int i=0;i<n;i++)
    {
        int x;  cin>>x;
        a.insert(x);
    }
    while (m--)
    {
        int x;  cin>>x;
        auto itr=a.upper_bound(x);
        if (itr==a.begin())
            cout<<-1<<endl;
        else {
            cout<<*(--itr)<<endl;
            a.erase(itr);
        }
    }
}
