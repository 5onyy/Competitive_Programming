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

int n,k,m;
const int N = 105;
vii delete_cell;
int a[N][15], vis[N][15];

bool inside(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= m;
}

void dfs(int i, int j) {
    if (vis[i][j])      return;
    vis[i][j] = 1;
    delete_cell.pb({i,j});
    for (int k = 0; k < 4; k++) {
        int u = td[k] + i;
        int v = tc[k] + j;
        if (!inside(u,v) || a[u][v] != a[i][j]) continue;
        if (!vis[u][v])     dfs(u,v);
    }
    return;
}

void print_matrix() {
    for (int i = 1; i <= n; i++)    {
        for (int j = 1; j <= m; j++)    cout << a[i][j];
        cout <<'\n';
    }
    //cout << '\n';
}

bool try_to_delete() {
    memset(vis, 0, sizeof vis);
    bool flag = 0;
    delete_cell.clear();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != 0 && !vis[i][j])    {
                delete_cell.clear();
                dfs(i,j);
                if (sz(delete_cell) >= k) {
                    for (auto [x, y] : delete_cell)     a[x][y] = 0;
                    flag = 1;
                }
            }
        }
    }
    //print_matrix();
    return flag;
}

void apply_gravity() {
	for (int j = 1; j <= 10; j++) {
		int next = n;   // next luu so 0 duoi cung, neu gap a[i][j] != 0 thi move next len de tranh TH
		for (int i = n; i >= 1; i--) {
			if (a[i][j] != 0) {
                swap(a[i][j], a[next][j]);
				next--;
			}
		}
	}
    //print_matrix();
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        string s;   cin >> s;
        m = sz(s);
        for (int j = 0; j < m; j++)     a[i][j + 1] = s[j] - '0';
    }
    while (try_to_delete() == true) {
        apply_gravity();
    }
    print_matrix();
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    freopen("mooyomooyo.in", "r", stdin);
    freopen("mooyomooyo.out", "w", stdout);
    solve();
    return 0;
}
