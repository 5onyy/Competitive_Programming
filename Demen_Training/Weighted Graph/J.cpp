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

const int N = 1e5 + 5;
vii adj[N];
int n,m,q;
int dp[2][N];

void dijkstra(int s) {
    for (int i = 0; i < 2; i++) for (int j = 0; j < N; j++) dp[i][j] = INF;
    minpq<iii> pq;
    dp[0][s] = 0, dp[1][s] = 0;
    pq.push({0,{0,s}});
    while (sz(pq)) {
        auto top = pq.top();    pq.pop();
        int d_u = top.F, state = top.S.F, u = top.S.S;
        // if (d_u != dp[0][u])    continue;
        for (auto [v,w] : adj[u]) {
            if (dp[0][v] > dp[0][u] + w) {
                dp[0][v] = dp[0][u] + w;
                pq.push({dp[0][v],{0,v}});
            }
            if (state == 0 && dp[1][v] > dp[0][u]) {
                dp[1][v] = dp[0][u];
                pq.push({dp[1][v], {1,v}});
            }
            if (state == 1 && dp[1][v] > dp[1][u] + w) {
                dp[1][v] = dp[1][u] + w;
                pq.push({dp[1][v], {1,v}});
            }
        }
    }
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        int u,v,w;  cin >> u >> v >> w;
        adj[u].pb({v,w});
    }
    dijkstra(1);
    // for (int i = 0; i < 2; i++)     {
    //     for (int j = 1; j <= n; j++)    cerr << dp[i][j] << ' ';
    //     cerr << '\n';
    // }
    while (q--) {
        int s,t0;   cin >> s >> t0;
        // cerr << dp[0][s] << " , " << dp[1][s]<< '\n';
        cout << min(dp[0][s], dp[1][s] + t0) << '\n';
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
