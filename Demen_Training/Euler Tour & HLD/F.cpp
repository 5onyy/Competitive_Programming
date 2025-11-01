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

const int N = 2e5 + 5;
const ll INF = 1e18 + 5;
const int inf = 2e9 + 5;
const int MOD = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

int d[N], euler[N], tin[N], tout[N];
int dfsTime;
vi adj[N];
vi seg[4 * N];

void eulerTour(int u, int par = -1) {
    euler[++dfsTime] = d[u];
    tin[u] = dfsTime;
    for (int v : adj[u])    if (v != par) {
        d[v] = d[u] + 1;
        eulerTour(v,u);
    }
    tout[u] = dfsTime;
}

vi merge(vi &a, vi &b) {
    int n = sz(a), m = sz(b);
    int i = 0, j = 0;
    vi ans;
    while (i < n && j < m) {
        if (a[i] < b[j])    ans.pb(a[i]),   i++;
        else ans.pb(b[j]),  j++;
    }
    while (i < n)   ans.pb(a[i]),   i++;
    while (j < m)   ans.pb(b[j]),   j++;
    return ans;
}

void build(int id, int l, int r) {
    if (l == r)     {
        seg[id].pb(euler[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
    // cerr << id << " : \n";
    // for (int v : seg[id])   cerr << v << " ";
    // cerr << endl;
}

int get(int id, int l, int r, int u, int v, int k) {
    if (l > v || r < u)     return 0;
    if (l >= u && r <= v)   
        return upper_bound(all(seg[id]), k) - 
        lower_bound(all(seg[id]), k);
    int mid = (l + r) / 2;
    int lhs = get(id * 2, l, mid, u, v, k);
    int rhs = get(id * 2 + 1, mid + 1, r, u, v, k);
    return lhs + rhs;
}

void solve() {
    int n;  cin >> n;
    for (int i = 2; i <= n; i++) {
        int v;  cin >> v;
        adj[v].pb(i);
    }
    eulerTour(1);
    build(1,1,n);
    // for (int  v : seg[1])   cerr << v << " ";
    // cerr << '\n';
    int q;  cin >> q;
    while(q--){
        int ui,di;  cin >> ui >> di;
        // cerr << tin[ui] << " " << tout[ui] << " " << di + d[ui] << endl;
        int ans = get(1,1,n,tin[ui], tout[ui], di);
        cout << ans << '\n';
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("promote.in", "r", stdin);
    // freopen("promote.out", "w", stdout);
    solve();
    return 0;
}
