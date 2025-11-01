#include<bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define sz(x) (int)(x).size()
#define sqr(x) ((x) * (x))
#define log2i(x) (64 - __builtin_clzll(1ll * (x)) - 1)
#define all(x)         x.begin(),x.end()
#define rall(x)        x.rbegin(),x.rend()
#define debug(x) { cout << #x << " = "; cout << (x) << endl; }
#define rr(x)          sort(all(x)),x.resize((unique(all(x))-x.begin()));

template<typename T> using vt = vector<T>;
using ll = long long;
using ld = long double;
using vi = vt<int>;
using ii = pair<int, int>;
using vii = vt<ii>;

const ll INF=4e18;
const int inf=INT_MAX;
const int MOD=1000000003;
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

int n,s;
vt<ll> k,w,v;
ll dp[2001][2001] = {0};
ll f[2001][2001];
ll best[3005][3005];
map<ll,vt<pair<ll,ll>>> weight_group;

void sub4(){
    for (int i=1;i<=n;i++){
        for (int j=0;j<=s;j++){
            dp[i][j] = dp[i-1][j];
            int cnt = min(k[i],j/w[i]);
            for (int c=1;c<=cnt;c++){
                if (j - c*w[i] >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j-c*w[i]] + c*v[i]);
                //cout<<i<<' '<<j<<' '<<c<<'\n';
                //debug(dp[i][j]);
            }
        }
        //cout<<'\n';
    }
    cout<<dp[n][s];
}

void sub2(){
    for (int i=1;i<=n;i++){
        for (int j=0;j<=s;j++){
            f[i][j] = f[i-1][j];
            if (j>=w[i])         f[i][j] = max(f[i][j], f[i-1][j-w[i]]+v[i]);
        }
    }
    cout<<f[n][s];
}

void sub5(){
    int index=1;
    ll ans=0;
    for (auto &[_w,items] : weight_group){
        sort(items.begin(),items.end(),greater<>());
        //for (int i = 0 ;i < items.size() ;i++)  debug(items[i]);
        for (int j=0;j<=s;j++){
            best[index][j] = best[index-1][j];
            ll cur_used=0;
            ll num=0;
            ll pos=0;
            ll tot=0;
            //cout<<index<<' '<<j<<'\n';
            while ( (num+1)*_w <= j && pos < items.size() ){
                num++;
                cur_used++;
                tot += items[pos].fi;
                best[index][j] = max(best[index - 1][j-num*_w] + tot, best[index][j]);
                ans=max(ans,best[index][j]);
                if (cur_used == items[pos].se){
                    cur_used = 0;
                    pos++;
                }
            }
            //debug(num);
            //debug(best[index][j]);
        }
        index++;
    }
    cout<<ans;
}

int main(){
    setIO("");
    cin>>s>>n;
    k.resize(n+1,0);
    w.resize(n+1,0);
    v.resize(n+1,0);
    for (int i=1;i<=n;i++){
        cin>>v[i]>>w[i]>>k[i];
        weight_group[w[i]].push_back({v[i],k[i]});
    }
    if (n==1)   {cout<<min(k[1],s/w[1]) * v[1]; return 0; }
    else sub5();
}

/* https://oj.uz/problem/view/NOI18_knapsack */
/*g++ -std=c++17 -O2 -Wall "knapsack.cpp" -o main.exe
./main.exe*/
