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

vi par;

int find_root(int v) {
    return (par[v] < 0) ? v : par[v] = find_root(par[v]);
}

void merge(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b)     return;
    if (par[a] > par[b])    swap(a,b);
    par[a] += par[b];
    par[b] = a;
}

struct Query {
    int id, u, w;
    bool operator < (Query x) {
        return w > x.w;
    }
};

const int N = 1e5 + 5;
vii edges[N];   // edges[i], all edges with weight = i;

void solve() {
    int n,m,q;  cin >> n >> m >> q;
    par = vi(n + 1, -1);
    vi weights, ans(q);
    vt<Query> queries(q);
    for (int i = 1; i <= m; i++) {
        int u,v,w;      cin >>u >> v >> w;
        edges[w].pb({u,v});
        weights.pb(w);
    }
    
    for (int i = 0; i < q; i++) {
        cin >> queries[i].u >> queries[i].w;
        queries[i].id = i;
    }
    sort(all(queries));
    
    rr(weights);
    reverse(all(weights));
    // for (int i = 0; i < sz(weights); i++)     cerr << weights[i] << ' ' ;
    // cerr << '\n';
    // for (int i = 0; i < q; i++)     cerr << queries[i].u << ' ' << queries[i].w << '\n';
        
    int i = 0;
    for (int j = 0; j < q; j++) {
        for (; weights[i] >= queries[j].w && i < sz(weights); i++) {
            int w = weights[i];
            if (sz(edges[w]) > 0) {
                for (auto [u,v] : edges[w]) {
                    // cerr << u << ' ' << v << '\n';
                    merge(u,v);
                }
            }
        }
        int id = queries[j].id;
        ans[id] = -par[find_root(queries[j].u)];
        // cerr << '\n';
    }
    for (int i : ans)   cout << i << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
