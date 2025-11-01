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

const int N = 1e6;
const ll INF = 1e18 + 5;
const int inf = 2e9 + 5;
const int MOD = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

const int LG = 22;
vi adj[N];
int tin[N], tout[N], d[N];
int dfsTime,q,n;
ii spt[N][LG], euler[N];

void dfs(int u, int par = -1) {
    tin[u] = ++dfsTime;
    euler[dfsTime] = {d[u], u};
    for (int v : adj[u])    if (v != par) {
        d[v] = d[u] + 1;
        dfs(v,u);
        euler[++dfsTime] = {d[u], u};
    }
    tout[u] = dfsTime;
}

void build() {
    for (int i = 1; i <= dfsTime; i++)        spt[i][0] = {euler[i].f, euler[i].s};
    for (int j = 1; j < LG; j++)    for (int i = 1; i + (1 << j) - 1 <= dfsTime; i++) {
        spt[i][j] = min(spt[i][j - 1], spt[i + (1 << (j - 1))][j - 1]);
    }
}

ii query(int l, int r) {
    if (r < l)  swap(l,r);
    int k = __lg(r - l + 1);
    return min(spt[l][k], spt[r - (1 << k) + 1][k]);
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i < n; i++)     {
        int u,v;    cin >> u >> v;
        adj[u].pb(v);   adj[v].pb(u);
    }
    dfs(1);
    // for (int i = 1; i <= dfsTime; i++)      cerr << "(" << euler[i].f << "," << euler[i].s << ") ";
    // cerr << endl;
    build();
    while (q--) {
        int u,v;    cin >> u >> v;
        // cerr << tin[u] << " " << tin[v] << endl;
        int lca = query(tin[u], tin[v]).s;
        cout <<  d[u] + d[v] - 2 * d[lca] << '\n';
    }
    
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
