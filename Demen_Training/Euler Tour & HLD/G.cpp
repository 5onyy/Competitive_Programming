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

const int N = 4e5 + 5;
const ll INF = 1e18 + 5;
const int inf = 2e9 + 5;
const int MOD = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

int d[N], in[N], out[N];
vii adj[N];
ii euler[N], spt[N][20];
int dfsTime;

void euler_tour(int u, int par = -1) {
    ++dfsTime;
    in[u] = dfsTime;
    euler[dfsTime] = {d[u], u};
    for (auto [v,w] : adj[u])  if (v != par) {
        d[v] = d[u] + w;
        euler_tour(v,u);
        euler[++dfsTime] = {d[u], u};
    }
    out[u] = dfsTime;
}

void build_spt() {
    for (int i = 1; i <= dfsTime; i++)      spt[i][0] = euler[i];
    for (int j = 1; j < 20; j++)    for (int i = 1; i + (1 << j) - 1<= dfsTime; i++) {
        spt[i][j] = min(spt[i][j - 1], spt[i + (1 << (j - 1))][j - 1]);
    }
}

ii query(int l, int r) {
    if (r < l)  swap(l,r);
    int k = __lg(r - l + 1);
    return min(spt[l][k], spt[r - (1 << k) + 1][k]);
}

int lca(int u, int v) {
    return query(in[u], in[v]).s;
}

struct FT {
    int n;
    vi fen;
    FT (int _n) : n(_n) {fen.assign(n + 5,0);};
    void update(int pos, int val)   {
        for (; pos <= n; pos += pos & -pos)     fen[pos] += val;
    }
    int get(int pos) {
        int ans = 0;
        for (; pos > 0; pos -= pos & -pos)  ans += fen[pos];
        return ans;
    }
    void range_update(int l, int r, int val) {
        update(l, val);
        update(r + 1, -val);
    }
};

bool cha(int u, int v) {    /// Check if u is parent of v
    return (in[u] <= in[v] && out[u] >= out[v]);
}

void solve() {
    int n;      cin >> n;
    vt<array<int,3>> edge(n + 1);
    for (int i = 1; i < n; i++) {
        int u,v,w;      cin >> u >> v >> w;
        edge[i] = {u,v,w};
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    euler_tour(1);
    build_spt();
    FT fen(2 * n - 1);
    for (int i = 1; i <= 2 * n - 1; i++)    {
        fen.update(i, euler[i].f - euler[i - 1].f);
    }
    int q;  cin >> q;
    while (q--) {
        int typ;    cin >> typ;
        if (typ == 1) {
            int id;     cin >> id;
            int nval;    cin >> nval;
            int u = edge[id][0], v = edge[id][1];
            if (!cha(u,v))  swap(u,v);
            fen.range_update(in[v], out[v], nval - edge[id][2]);
            edge[id][2] = nval;
        }
        else {
            int u,v;    cin >> u >> v;
            cout << fen.get(in[u]) + fen.get(in[v]) - 2 * fen.get(in[lca(u,v)]) << endl;
        }
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
