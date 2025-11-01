
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
const int mod = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

const int N = 305;

int n,m, cnt;
int d[N][N], connect[N][N], vis[N];

void floyd() {
    for (int i = 1; i <= n; i++)    d[i][i] = 0;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

void dfs(int s) {
    if (vis[s])     return;
    vis[s] = 1;
    ++cnt;
    for (int t = 1; t <= n; t++)    if (connect[s][t] && !vis[t])   dfs(t);
    return;
}

void solve() {
    cin >> n >> m;
    vii edges;
    for (int i = 1; i <= m; i++) {
        int u,v,w;  cin >> u >> v >> w;
        d[u][v] = d[v][u] = w;
        connect[u][v] = connect[v][u] = 1;
        edges.pb({u,v});
    }
    floyd();
    int ans = 0;
    for (auto [u,v] : edges){
        memset(vis,0,sizeof vis);
        cnt = 0;
        connect[u][v] = connect[v][u] = 0;
        dfs(1);
        if (cnt == n) {
            bool f = 1;
            for (int i = 1; i <= n; i++)    if (d[i][u] + d[i][v] != d[u][v] && i != u && i != v) {cerr << i << ' ' << u << ' ' << v << '\n'; f = 0;  break;}
            if (f) ans++;
        }
        connect[u][v] = connect[v][u] = 1;
    }
    cout << ans;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
