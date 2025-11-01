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

const int N = 5005;
int n, m, start;
int d[N], par[N];

struct Edge {
    int u,v,w;
}edges[N];

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    memset(d, INF, sizeof d);
    for (int i = 0; i < N; i++) par[i] = -1;
    for (int i = 0; i < n; i++) {
        start = -1;
        for (int j = 1; j <= m; j++) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (d[u] < INF) {
                if (d[v] > d[u] + w) {
                    d[v] = max(-INF, d[u] + w);
                    par[v] = u;
                    start = v;
                }
            }
        }
    }
    
    if (start == -1)    cout << "NO";
    else {
        cerr << start << ' ';
        for (int i = 0; i < n; i++)     {
            start = par[start];
            cerr << start << ' ';
        }
        vi cycle;
        for (int v = start; ; v = par[v]) {
            cycle.pb(v);
            if (v == start && sz(cycle) > 1)    break;
        }
        reverse(all(cycle));
        cout << "YES\n";
        for (int v : cycle) cout << v << ' ';
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
