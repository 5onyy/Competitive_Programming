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
#define timer cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";

using ll = long long;
using ii = pair<int, int>;
using iii = pair<int, ii>;

const int N = 305;
const ll INF = numeric_limits<long long>::max() / 2;
const int MOD = 1e9 + 7;

template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

int a[N],b[N];
int c[N][N], par[N], f[N][N], d[N];
int n,m,s,t,k;

int bfs(int s, int t) {
    queue<int> q;
    fill(par, par + N, -1);
    fill(d, d + N, 0);
    q.push(s);  d[s] = INF;
    while (!q.empty()) {
        int u = q.front();      q.pop();
        for (int i = 0; i <= n + m + 1; i++) {
            if (c[u][i] - f[u][i] > 0 && par[i] == -1) {
                d[i] = min(d[u], c[u][i] - f[u][i]);
                par[i] = u;     q.push(i);
                if (i == t)     return d[t];
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int cur = 0, ans = 0;
    while ((cur = bfs(s,t)) > 0) {
        ans += cur;
        int v = t;
        while (v != s) {
            f[par[v]][v] += cur;
            f[v][par[v]] -= cur;
            v = par[v];
        }
    }
    return ans;
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)        {
        cin >> a[i];
        c[0][i] = a[i];
    }   
    for (int i = 1; i <= m; i++)        {
        cin >> b[i];
        c[i+n][n + m + 1] = b[i];
    }
    while (k--) {
        int i,j;    cin >> i >> j;
        c[i][j+n] = INF;
    }
    cout << max_flow(0,n+m+1);
}


signed main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
