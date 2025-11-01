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

const int N = 2e5 + 5;
vi group[N], adj[N];
int p[N][20], h[N];

void dfs(int u, int par) {
    p[u][0] = par;
    for (int i = 1; i < 20; i++)    p[u][i] = p[p[u][i - 1]][i - 1];
    for (int v : adj[u])    if (v != par) {
        h[v] = h[u] + 1;
        dfs(v,u);
    }
}

int lca(int u, int v) {
    if (h[u] < h[v])        swap(u,v);
    int k = h[u] - h[v];
    for (int i = 0; i < 20; i++)    if (k >> i & 1)     u = p[u][i];
    if (u == v)     return u;
    for (int i = 19; i >= 0; i--)       if (p[u][i] != p[v][i])     u = p[u][i], v = p[v][i];
    return p[u][0];
}

int distance(int u, int v) {
    return h[u] + h[v] - 2 * h[lca(u,v)];
}

int diameter(const vi &vs) {
    int mx = 0;
    int a = vs[0], b = vs[0];
    for (int i = 1; i < sz(vs); i++) {
        int dis = distance(vs[i], vs[0]);
        if (mx < dis){
            mx = dis;
            a = vs[i];
        }
    }
    mx = 0;
    for (int i = 0; i < sz(vs); i++)    {
        int dis = distance(vs[i], a);
        if (vs[i] != a && mx < dis) {
            mx = dis;
            b = vs[i];
        }
    }
    return mx;
}

void solve() {
    int n;  cin >> n;
    int k;  cin >> k;
    int root;
    for (int i = 1; i <= n; i++)    {
        int groupd_id, v;
        cin >> groupd_id >> v;
        group[groupd_id].pb(i);
        adj[i].pb(v);
        adj[v].pb(i);
        if (v == 0)     root = i;
    }
    dfs(root,0);
    for (int i = 1; i <= k; i++)    cout << diameter(group[i]) << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
