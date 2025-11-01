// Example: 

// 0 0 0 0 0 0 0 
// 0 0 0 0 0 0 0 
// 0 0 0 0 0 0 0 
// 0 0 0 1 -1 1 0 
// 0 0 0 0 0 -1 0 
// 0 0 0 0 -1 1 0 
// 0 0 0 0 0 0 0 

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// #define int long long
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

const int N = 101;
int a[N][N], vis[N][N];
int n,k,r,cnt;
map<ii,int> wall;


bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int stt(int x, int y) {
    return x * n + y;
}

void dfs(int x, int y) {
    if (vis[x][y])  return;
    vis[x][y] = cnt;
    for (int k = 0; k < 4; k++) {
        int xx = x + td[k];
        int yy = y + tc[k];
        if (!inside(xx,yy) || vis[xx][yy] || wall[{stt(x,y), stt(xx,yy)}])    continue;
        if (!vis[xx][yy])   dfs(xx,yy);
    }
    return;
}

void solve() {
    cin >> n >> k >> r;
    for (int i = 1; i <= r; i++)   {
        int x1, y1, x2,y2;  cin >> x1 >> y1 >> x2 >> y2;
        wall[{stt(x1,y1), stt(x2,y2)}] = 1;
        wall[{stt(x2,y2), stt(x1,y1)}] = 1;
    }
    vii cows;
    for (int i = 1; i <= k;i ++) {
        int x,y;    cin >> x >> y;
        cows.pb({x,y});
        a[x][y] = 1;
    }
    for (ii p : cows) {
        if (!vis[p.f][p.s]) {
            ++cnt;  dfs(p.f,p.s);
        }
    }
    int ans = 0;
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (vis[cows[i].f][cows[i].s] != vis[cows[j].f][cows[j].s]) ans++;
        }
    }
    cout << ans;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);
    solve();
    return 0;
}
