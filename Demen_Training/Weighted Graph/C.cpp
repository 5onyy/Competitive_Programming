// Solution:
// Bellman-Ford Algorithm for the nth iteration and mark the nodes whose distance is changed. Now reverse the adjacency list and run a DFS from node 'n'. If at least one of the nodes marked is visible from n, then the answer is -1, else the answer is the maximum distance from 1 to n.

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

const int N = 3000;
vi rev_adj[N];
vt<iii> edges;
int n,m;
int d[N], vis[N];
int del[N];

void bellmanFord (int s) {
    for (int i = 0; i < N; i++)     d[i] = -INF;
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        for (iii ed : edges) {
            int u = ed.F, v = ed.S.F, w = ed.S.S;
            if (d[u] > -INF) {
                if (d[v] < d[u] + w) {
                    if (i == n - 1)     del[v] = 1;
                    d[v] = min(INF, d[u] + w);
                }   
            }
        }
    }
}

void dfs(int u) {
    if (vis[u])     return;
    vis[u] = 1;
    for (int v : rev_adj[u])    if (!vis[v])    dfs(v);
    return;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)    {
        int u,v,w;  cin >> u >> v >> w;
        edges.pb({u,{v,w}});
        rev_adj[v].pb(u);
    }
    bellmanFord(1);
    dfs(n);
    // for (int i = 1; i <= n; i++)    cerr << d[i] << ' ';
    for (int i = 1; i <= n; i++)    if (vis[i] && del[i])     return void(cout << -1);
    cout << d[n];
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
