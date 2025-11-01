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

int cur;
vi p,del_ed;

struct Query {
    char typ;
    int id;
};

int get_root(int v) {
    return p[v] < 0 ? v : p[v] = get_root(p[v]);
}

void unite(int u, int v) {
    int a = get_root(u), b = get_root(v);
    if (a == b) return;
    if (p[a] > p[b])    swap(a,b);
    cur += p[a] * p[b];
    p[a] += p[b];
    p[b] = a;
} 

void solve() {
    int n;  cin >> n;
    cur = 0;
    p.assign(n + 5, -1), del_ed.assign(n + 5, 0);
    vt<ii> edges(n + 5);
    for (int i = 1; i < n; ++i) {
        cin >> edges[i].F >> edges[i].S;
    }
    int q;  cin >> q;
    vt<Query> queries(q + 1);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].typ;
        if (queries[i].typ == 'R')  {
            int id; cin >> id;
            queries[i].id = id;
            del_ed[id] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        if (!del_ed[i])                 unite(edges[i].F, edges[i].S);
    }
    vi ans;
    for (int i = q - 1; i >= 0; i--) {
        if (queries[i].typ == 'Q')  {
            ans.pb(n * (n - 1) / 2 - cur);
        }
        else {
            int id = queries[i].id;
            int u = edges[id].F, v = edges[id].S;
            unite(u,v);
        }
    }
    for (int i = sz(ans) - 1; i >= 0; i--)  cout << ans[i] << '\n';
    cout << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    int test;   cin >> test;
    while (test--)  solve();
    return 0;
}
