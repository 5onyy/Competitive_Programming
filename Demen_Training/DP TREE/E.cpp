#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long
#define f first
#define s second
#define pb push_back
#define sz(x) (int)(x).size()
#define sqr(x) ((x) * (x))
#define all(x)         x.begin(),x.end()
#define rr(x)          sort(all(x)),x.resize((unique(all(x))-x.begin()));
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define timer cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";

template<typename T> using vt = vector<T>;
using ll = long long;
using ld = long double;
using vi = vt<int>;
using ii = pair<int, int>;
using iii = pair<int, ii>;
using vii = vt<ii>;

const int N = 1e5 + 5;
const ll INF = 1e18 + 5;
const int inf = 2e9 + 5;
const int MOD = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

vii adj[N];
int dp[N], isLeaf[N], f[N];  
int inv2 = fpow(2, MOD-2, MOD);

void add(int &x, int y) {
    x+=y;   x %= MOD;
}

int mul(int x, int y) {
    x *= y;     x %= MOD;
    return x;
}

void sub(int &x, int y) {
    x -= y;     
    if (x < 0)      x += MOD;
}

void dfs(int u, int par = -1) {
    int fv_2 = 0;
    int fv = 0;
    for (auto [v,w] : adj[u])   if (v != par) {
        dfs(v,u);
        int tmp = mul(w, (f[v] + 1) % MOD);
        add(fv_2, tmp);
        add(fv, mul(tmp, tmp));
    }
    int fv2 = mul(fv_2, fv_2);
    sub(fv2, fv);
    fv2 = mul(fv2, inv2);
    
    add(f[u], fv_2);
    
    add(dp[u], f[u]);
    add(dp[u], fv2);
}

void solve() {
    int n;  cin >> n;
    for (int i = 1; i < n; i++)     {
        int u,v,w;      cin >> u >> v >> w;
        adj[u].pb({v,w});   adj[v].pb({u,w});
    }
    dfs(1);
    int res = 0;
    for (int i = 1; i <= n; i++)       add(res,dp[i]);
    cout << res;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
