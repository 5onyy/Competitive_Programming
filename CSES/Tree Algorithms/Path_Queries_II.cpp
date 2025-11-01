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

int sz[N];
int n, dfsTime;
int nhanh, cnt;
int id[N]; // <=> thu tu cua chain chua dinh i = id[i]
int head[N]; // <=> gia tri dau tien cua chain thu i = head[i]
int pos[N]; // <=> thu tu cua dinh u sau khi duoc trai phang = pos[i]
int in[N], out[N], h[N], a[N], p[N][20];
vi adj[N];

struct seg2D {  // 0-index
    int n;
    vi seg;
    seg2D() = default;
    seg2D(int _n) : seg(2 * _n, INT_MIN), n(_n) {}
    void update(int u, int val) {
        for (seg[u += n] = val; u > 1; u /= 2)    {
            seg[u >> 1] = max(seg[u], seg[u ^ 1]);
        }
    }
    int get(int u, int v) {
        int ans = INT_MIN;
        for (u += n,v += n; u <= v; u/=2, v /= 2) {
            if (u & 1)      ans = max(ans, seg[u++]);
            if (~v & 1)     ans = max(ans, seg[v--]);
        }
        return ans;
    }
}seg;


void reset() {
    nhanh = 1;
    dfsTime = 0;
    cnt = 0;
    for (int i = 1; i <= n; i++){
        adj[i].clear();
        h[i] = 0;
        in[i] = 0;
        out[i] = 0;
        pos[i] = 0;
        head[i] = 0;
        id[i] = 0;
        a[i] = 0;
        sz[i] = 1;
    }  
    memset(p,0,sizeof p);
}


void dfs(int u, int par = -1) {
    p[u][0] = par;
    for (int i = 1; i < 20; i++)        p[u][i] = p[p[u][i-1]][i-1];
    ++dfsTime;
    in[u] = dfsTime;
    sz[u] = 1;
    for (int v : adj[u])   if (v != par) {
        h[v] = h[u] + 1;
        dfs(v,u);
        sz[u]+=sz[v];
    }
    out[u] = dfsTime;
}

bool cha(int u, int v) {
    return (in[u] <= in[v] && out[u] >= out[v]);
}

void build_hld(int u, int par = -1) {
    if (head[nhanh] == 0) {
        head[nhanh] = u;
    }
    ++cnt;
    pos[u] = cnt;
    id[u] = nhanh;
    
    int tmp = -1;
    for (int v : adj[u])        if (v != par) {
        if (tmp == -1 || sz[tmp] < sz[v])       tmp = v;
    } // Tim dinh v co sz lon nhat
    
    // heavy edge
    if (tmp != -1)      build_hld(tmp,u);
    
    for (int v : adj[u])    if (v != par && v != tmp) {
        /// light edge
        nhanh++;
        build_hld(v,u);
    }
}

int ans_hld(int u, int v) {     // the maximum edge cost on the path from node u to node v
    int ans = INT_MIN;
    while (id[u] != id[v]) {
        if (h[head[id[u]]] > h[head[id[v]]])        swap(u,v);
        int v2 = head[id[v]];
        ans = max(ans, seg.get(pos[v2] - 1, pos[v] - 1));
        v = p[v2][0];
    }
    /// id[u] == id[v]
    if (pos[u] > pos[v])    swap(u,v);
    ans = max(ans, seg.get(pos[u] - 1, pos[v] - 1));
    return ans;
}
void precalc() {
    dfs(1,1);
    build_hld(1);
}

void solve() {
    cin >> n;
    int q;  cin >> q;
    for (int i = 1; i <= n; i++)    cin >> a[i];
    vt<array<int,3>> ed(n + 1);
    for (int i = 1; i < n; i++)     {
        int u,v;  cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    precalc();
    seg = seg2D(cnt);
    for (int i = 1; i <= n; i++) {
        seg.update(pos[i] - 1, a[i]);
    }
    while (q--) {
        int typ;    cin >> typ;
        if (typ == 1)       {
            int s,x;    cin >> s >> x;
            a[s] = x;
            seg.update(pos[s] - 1, x);
        }
        else {
            int u, v;   cin >> u >> v;
            if (!cha(u,v))      swap(u,v);
            cout << ans_hld(u,v) << ' ';
        }
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
