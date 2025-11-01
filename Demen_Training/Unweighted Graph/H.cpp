// SOurce: https://vjudge.net/contest/641580#problem/H
// Solution:
// Every vertex in a connected component can be automatically sorted --> A solution is possible when p[i] is in the same component as i
// Binary search the minimum width, called x --> in a component, every w_i in edges will be >= x --> Check if it is a valid solution (p[i] is in the same component as i).  BS for the max x

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

const ll INF = 1e18 + 5;
const int inf = 2e9 + 5;
const int mod = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

const int N = 1e5 + 5;

vi a[N];
int n, m;
int p[N], vis[N];
vt<iii> edges;

bool edgeCase() {
    for (int i = 1; i <= n; i++)    if (i != p[i])  return 0;
    return 1;
}

void dfs(int u, int cnt) {
    if (vis[u])     return;
    vis[u] = cnt;
    for (int v : a[u])      if (!vis[v])    dfs(v,cnt);
    return;
}

bool check(int x) {
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++)    a[i].clear();
    for (iii tmp : edges)  {
        int u = tmp.f, v = tmp.s.f, w = tmp.s.s;
        if (w >= x)     a[u].pb(v), a[v].pb(u);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)    {
        if (!vis[i])    {
            ++cnt;  dfs(i, cnt);
        }
    }
    for (int i = 1; i <= n; i++)    if (vis[i] != vis[p[i]])    return 0;
    return 1;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)            cin >> p[i]; 
    for (int i = 1; i <= m; i++)    {
        int u,v,w;      cin >> u >> v >> w;
        edges.pb({u,{v,w}});
    }
    if (edgeCase())   return void(cout << -1);
    int l = 0, r = 1e9, ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid))     ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << ans;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    solve();
    return 0;
}
