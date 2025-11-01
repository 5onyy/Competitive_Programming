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

const int N = 505;

int vis[N][N], a[N][N];
vii waypoints;
int n,m;    

bool inside(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= m;
}

void dfs(int x, int y, int D) {
    if (vis[x][y])  return;
    vis[x][y] = 1;
    for (int k = 0; k < 4; k++) {
        int xx = x + td[k];
        int yy = y + tc[k];
        if (!inside(xx,yy) || abs(a[x][y] - a[xx][yy]) > D) continue;
        if (!vis[xx][yy])   dfs(xx,yy,D);
    }
}

bool check(int D) {
    memset(vis, 0, sizeof vis);
    auto [x, y] = waypoints[0];
    dfs(x, y, D);
    for (auto [i,j] : waypoints)    if (!vis[i][j])     return false;
    return true;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)    for (int j = 1; j <= m; j++)    cin >> a[i][j];
    for (int i = 1; i <= n; i++)    for (int j = 1; j <= m; j++)    {
        int x;  cin >> x;   
        if (x == 1)     waypoints.pb({i,j});
    }
    int l = 0, r = 1e9, ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    cout << ans;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    freopen("ccski.in", "r", stdin);
    freopen("ccski.out", "w", stdout);
    solve();
    return 0;
}
