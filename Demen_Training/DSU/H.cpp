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

const int N = 2005;
int d[N][N];
vii adj[N];
vt<array<int,3>> edges;
vi par, h;
int n;

int get_root(int v) {
    return par[v] < 0 ? v : par[v] = get_root(par[v]);
}

bool unite(int u, int v) {
    int a = get_root(u), b = get_root(v);
    if (a == b)     return false;
    if (par[a] > par[b])    swap(a, b);
    par[a] += par[b];
    par[b] = a;
    return true;
}

void kruskal() {
    sort(all(edges), [] (array<int, 3> &a, array<int, 3> &b) {
       return a[2] < b[2]; 
    });
    for (auto [u,v,w] : edges) {
        // cerr << u << ' ' << v << ' ' << w << '\n';
        if (unite(u,v)) adj[u].pb({v,w}),   adj[v].pb({u,w});
    }
}

void dfs(int u, int p, int dep = 0) {
    h[u] = dep;
    for (auto [v,w] : adj[u])   if (v != p)     dfs(v,u,w + h[u]);
}

bool check() {
    for (int i = 1; i <= n; i++) {
        h.assign(n + 1, 0);
        dfs(i,i);
        for (int j = 1; j <= n; j++) {
            if (h[j] != d[i][j])    return false;
            if (d[i][j] == 0 && i != j) return false;   // Vi positive weight nen duong di u -> v luon > 0
        }
    }
    return true;
}

void solve() {
    cin >> n;
    par.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)    {
            cin >> d[i][j];
            if (i != j) edges.pb({i,j,d[i][j]});
        }
    }
    kruskal();
    if (check())    cout << "YES";
    else cout << "NO";
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
