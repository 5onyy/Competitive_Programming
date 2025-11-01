/// Solution: Gộp tất cả các đỉnh trong tập chu trình S_i lại, nối tất cả các đỉnh đó với 1 đỉnh ảo. Không mất tính tổng quát, ta có đường đi từ u->v trong chu trình cũ tương ứng với đưởng đi từ u->đỉnh ảo->v. Vậy cây MST với x cạnh trong đồ thị ban đầu sẽ bằng cây MST với x + 1 cạnh trong đồ thị lúc sau. Cây MST cuối cùng sẽ bao gồm n+m đỉnh với n đỉnh thật và m đỉnh ảo, n + m - 1 cạnh. Trong đó sẽ có n - 1 cạnh real và m cạnh trung gian có cost là c_i để nối từ các đỉnh real đếm m đỉnh ảo. Vậy đáp án sẽ là MST - sum(c_i)

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

int n,m, ans;
vi par;
vt<array<int,3>> edges;

int find_root(int v)  {
    return par[v] < 0 ? v : par[v] = find_root(par[v]);
}

bool unite(int u, int v) {
    int a = find_root(u), b = find_root(v);
    if (a == b)     return false;
    if (par[a] > par[b])    swap(a,b);
    par[a] += par[b];
    par[b] = a;
    return true;
}

bool kruskal() {
    sort(all(edges), [&] (array<int, 3> a, array<int, 3> b){
        return a[2] < b[2];
    });
    int cnt = 0;
    for (auto e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (unite(u,v)) cnt++,  ans += w;
    }
    if (cnt != n + m - 1)   return false;
    return true;
}

void solve() {
    cin >> n >> m;
    par.assign(5 * n, -1);
    vi cost;
    for (int i = 1; i <= m; i++) {
        int k,c;    cin >> k >> c;
        cost.pb(c);
        for (int j = 1; j <= k; j++) {
            int u;  cin >> u;
            edges.pb({n + i, u, c});
        }
    }
    if (!kruskal())     cout << -1;
    else cout << ans - accumulate(all(cost), 0LL);
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
