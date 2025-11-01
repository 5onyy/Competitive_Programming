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

int vis[N], ans = INF;
vi adj[N];

struct Point {
    int x, y;
}cows[N];

int calc(int s) {
    queue<int> q;
    int x_min = INF, y_min = INF, x_max = -INF, y_max = -INF;
    vis[s] = 1;
    q.push(s);
    while (sz(q)) {
        int u = q.front();  q.pop();
        x_min = min(x_min, cows[u].x);
        y_min = min(y_min, cows[u].y);
        x_max = max(x_max, cows[u].x);
        y_max = max(y_max, cows[u].y);
        for (int v : adj[u])    if (!vis[v])    vis[v] = 1, q.push(v);
    }
    return 2*(x_max - x_min + y_max - y_min);
}

void solve() {
    int n,m;    cin >> n >> m;
    for (int i = 1; i <= n; i++)    cin >> cows[i].x >> cows[i].y;
    for (int i = 1; i <= m; i++)    {
        int u,v;    cin >> u >> v;
        adj[u].pb(v);   adj[v].pb(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i])   ans = min(ans, calc(i));
    }
    cout << ans;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);
    solve();
    return 0;
}
