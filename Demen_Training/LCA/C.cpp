#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long
#define F first
#define S second
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

const ll INF = 1e18 + 5;
const int inf = 2e9 + 5;
const int MOD = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

const int N = 1e3 + 5;
int d[N],h[N];
int p[N][15];
vii adj[N];

void dfs(int u, int par) {
    p[u][0] = par;
    for (int i = 1; i < 15; i++)    p[u][i] = p[p[u][i - 1]][i - 1];
    for (auto [v,w] : adj[u]) {
        if (v == par)       continue;
        d[v] = d[u] + w;
        h[v] = h[u] + 1;
        dfs(v,u);
    }
}

int lca(int u, int v) {
    if (h[u] < h[v])    swap(u,v);
    int k = h[u] - h[v];
    for (int i = 0; i < 15; i++)    if (k >> i & 1)     u = p[u][i];
    if (u == v)     return u;
    for (int i = 14; i >= 0; i--)   if (p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
    return p[u][0];
}

void solve() {
    int n;  cin >> n;
    int q;  cin >> q;
    for (int i = 1; i < n; i++)     {
        int u,v,w;    cin >> u >> v >> w;
        adj[u].pb({v,w});   adj[v].pb({u,w});
    }
    dfs(1,1);
    while (q--) {
        int u,v;    cin >> u >> v;
        cout << d[u] + d[v] - 2 * d[lca(u,v)] << '\n';
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
