#include<bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define sz(x) (int)(x).size()
#define sqr(x) ((x) * (x))
#define all(x)         x.begin(),x.end()
#define rall(x)        x.rbegin(),x.rend()
#define debug(x) { cout << #x << " = "; cout << (x) << endl; }
#define rr(x)          sort(all(x)),x.resize((unique(all(x))-x.begin()));
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

template<typename T> using vt = vector<T>;
using ll = long long;
using ld = long double;
using vi = vt<int>;
using ii = pair<int, int>;
using vii = vt<ii>;

const ll INF=4e18;
const int inf=INT_MAX;
const int d4i[4]={-1, 0, 1, 0}, d4j[4]={0, 1, 0, -1};
const int d8i[8]={-1, -1, 0, 1, 1, 1, 0, -1}, d8j[8]={0, 1, 1, 1, 0, -1, -1, -1};

template<class U, class V> std::ostream& operator << (std::ostream& out, const std::pair<U, V>& p) {return out << '(' << p.first << ", " << p.second << ')';}   //cout pair type
template<typename T> using minpq = priority_queue<T, vt<T>,greater<T>>;
template<typename T> using maxpq = priority_queue<T>;

ll fgcd(ll a, ll b) {while(b) swap(b, a %= b); return a;}
ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for(; b; b >>= 1, a = a * a % c) if(b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
int flog(int x) {return 31 - __builtin_clz(x);}
int flog(ll x) {return 63 - __builtin_clzll(x);}

void setIO(string name) {
    cin.tie(0)->sync_with_stdio(0);
    if(sz(name)) {
        freopen((name+".inp").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}



const int maxN = 2e5 + 5;
int n;
int le[maxN],ri[maxN];

int main(){
    setIO("");
    cin>>n;
    vii a(n+1);
    vi pref(maxN,0);
    for (int i=1;i<=n;i++){
        cin>>a[i].fi>>a[i].se;
        a[i].se--;
        pref[a[i].fi]++;
        pref[a[i].se+1]--;
        //cout<<a[i].fi<<' '<<pref[a[i].fi]<<' '<<a[i].se<<' '<<pref[a[i].se]<<'\n';
        le[i] = a[i].fi;
        ri[i] = a[i].se;
    }
    int ans2=0;
    for (int i=1;i<maxN;i++){
        pref[i] += pref[i-1];
        ans2 = max(ans2,pref[i]);
    }
    sort(le+1,le+n+1);
/*     for (int i=0;i<n;i++)   cout<<le[i]<<' ';
    cout<<'\n'; */
    sort(ri+1,ri+n+1);
/*     for (int i=0;i<n;i++)   cout<<ri[i]<<' ';
    cout<<'\n'; */
    int ans1=-1;
    for (int i=1;i<=n;i++){
        int r = upper_bound(le+1,le+n+1,a[i].se) - le;
        int l = lower_bound(ri+1,ri+n+1,a[i].fi) - ri;
        //debug(i);   debug(l); debug(n-r-1);
        r--;
        int tmp = n - (l-1) - (n-r);
        ans1 = max(ans1,tmp);
        //debug(ans1);
    }
    cout<<ans1<<' '<<ans2;
}
