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
const int INF = numeric_limits<long long>::max() / 2;
const int mod = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

const int K = 21;
vi adj[N];
int dp[N][K], color[N];

void dfs(int u, int par = -1) {
    for (int v : adj[u])  if (v != par) {
        dfs(v,u);
        for (int color_u = 1; color_u < K; color_u++) {
            int mn = INF;
            for (int color_v = 1; color_v < K; color_v++)  {
                if (color_u != color_v) {
                    mn = min(mn, dp[v][color_v]);
                }
            }
            dp[u][color_u] += mn;
        }
    }
    for (int i = 1; i < K; i++)     dp[u][i] += i;
}

void dfs_trace(int u, int color_par = -1, int par = -1) {
    int mn = INF, color_id = 1;
    for (int c = 1; c < K; c++) if (c != color_par) {
        if (mn > dp[u][c])  {
            mn = dp[u][c];
            color_id = c;
        }
    }
    color[u] = color_id;
    for (int v : adj[u])  if (v != par) {
        dfs_trace(v, color_id ,u);
    }
}


void solve() {
    int n;  cin >> n;
    for (int i = 1; i < n; i++) {
        int u,v;    cin >> u >> v;
        adj[u].pb(v);   adj[v].pb(u);
    }
    if (n == 1)     return void(cout << "1\n1");
    dfs(1);
    int ans = INF;
    for (int i = 1; i < K; i++)     ans = min(ans, dp[1][i]);
    cout << ans << '\n';
    dfs_trace(1);
    for (int u = 1; u <= n; u++)    cout << color[u] << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
