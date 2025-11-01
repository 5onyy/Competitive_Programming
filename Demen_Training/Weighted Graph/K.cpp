#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// #define int long long
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
const int inf = 1061109567;
const int mod = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

const int K = 10005;

int n,k,r, ans;
int dp[101][K];
vt<iii> adj[101];

void dijkstra(int s) {
    memset(dp, 0x3f, sizeof dp);
    // cerr << dp[s][0] << '\n'; 
    minpq<iii> pq;
    dp[s][0] = 0;
    pq.push({0,{0, s}});
    while (sz(pq)) {
        iii top = pq.top();     pq.pop();
        int d_u = top.F, cur_money = top.S.F, u = top.S.S;
        // cerr << "u:" <<  u << " cur_money: " << cur_money << '\n';
        for (iii tmp : adj[u]) {
            int v = tmp.F, w = tmp.S.F, cost = tmp.S.S;
            // cerr << v << ' ' << w << ' ' << cost << '\n';
            if (cur_money + cost <= k && dp[v][cur_money + cost] > dp[u][cur_money] + w) {
                dp[v][cur_money + cost] = dp[u][cur_money] + w;
                if (v == n)     ans = min(ans, dp[u][cur_money] + w);
                pq.push({dp[v][cur_money + cost], {cur_money + cost, v}});
            }
        }
    }
}

void solve() {
    cin >> k >> n >> r;
    for (int i = 1; i <= n; i++)    adj[i].clear();
    for (int i = 1; i <= r; i++) {
        int u,v,w,cost;  cin >> u >> v >> w >> cost;
        adj[u].pb({v,{w,cost}});
    }
    ans = inf;
    dijkstra(1);
    if (ans == inf) cout << -1 << '\n';
    else    cout << ans << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    int test;   cin >> test;
    while (test--)    solve();
    return 0;
}
