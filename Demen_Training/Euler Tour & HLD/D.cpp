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

int c[N], tin[N], tout[N], euler[N], ans[N];
int dfsTime, n;
vi adj[N];

struct FT {
    int fen[N];
    void update(int pos, int val)       {
        for (; pos <= n; pos += pos & -pos)     fen[pos] += val;
    }
    int get(int pos) {
        int sum = 0;
        for (; pos > 0; pos -= pos & -pos)      sum += fen[pos];
        return sum;
    }
}BIT;

void eulerTour(int u, int par = -1) {
    tin[u] = ++dfsTime;
    euler[dfsTime] = u;
    for (int v : adj[u])    if (v != par) {
        eulerTour(v,u);
    }
    tout[u] = dfsTime;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)        cin >> c[i];
    for (int i = 1; i < n; i++)     {
        int u,v;    cin >> u >> v;
        adj[u].pb(v);    adj[v].pb(u);
    }
    eulerTour(1);
    // for (int i = 1; i <= n; i++)        //cerr << euler[i] << " ";
    //cerr << '\n';
    /// Xet tin giam dan
    unordered_map<int, int> last_idx;
    for (int time = n; time >= 1; time--) {
        int u = euler[time];
        //cerr << u << " : " << c[u] << " " << tin[u] << " " << tout[u] << " ";
        if (last_idx.count(c[u]))   BIT.update(last_idx[c[u]], -1);
        last_idx[c[u]] = time;
        BIT.update(last_idx[c[u]], 1);
        ans[u] =  BIT.get(tout[u]);
        ////cerr << last_idx[c[u]] << endl;
    }
    for (int i = 1; i <= n; i++)    cout << ans[i] << " ";
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
