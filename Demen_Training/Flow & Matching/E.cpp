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

const int N = 105;
const ll INF = numeric_limits<long long>::max() / 2;
const int MOD = 1e9 + 7;

template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

int c[N][N], par[N], f[N][N], d[N], cost[N][N], vis[N];
int n,m,s,t;
int ans, num_del;

int bfs(int s, int t) {
    queue<int> q;
    fill(par + 1, par + N, -1);
    fill(d + 1, d + N, 0);
    q.push(s);  d[s] = INF;
    while (!q.empty()) {
        int u = q.front();      q.pop();
        for (int i = 1; i <= n; i++) {
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

void dfs(int u) {
    vis[u] = 1;
    for (int v = 1; v <= n; v++)        {
        if (abs(f[u][v]) < c[u][v] && !vis[v])     dfs(v);
    }
}

void solve() {
    cin >> n >> m;
    int l = 0, r = 10;
    for (int i = 1; i <= m; i++) {
        int u,v,C;  cin >> u >> v >> C;
        cost[u][v] += C;
        cost[v][u] += C;
        // l = min(l, C);
        // r = max(r, C);
    }    
    int mid = 0;
    cin >> s >> t;
    while (l <= r) {
        mid = (l + r) / 2;
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j || !cost[i][j])     continue;
                c[i][j] = 0;
                if (cost[i][j] > mid)      c[i][j] = 1;         // Nhung canh u-v co cost < mid thi se khong tham gia vao trong lat cat (Do cac cong viec thuc hien song song) => chi can cat nhung canh > mid
            }
        }
        
        // for (int i = 1; i <= n; i++)    {
        //     for (int j = 1; j <= n; j++)        cerr << c[i][j] << " ";
        //     cerr << '\n';
        // }
        int cur = max_flow(s,t);
        // cerr << mid << " -> " << cur << "\n\n";
        if (!cur) {
            num_del = cur;
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j || !cost[i][j])     continue;
            c[i][j] = INF;
            if (cost[i][j] <= ans)      c[i][j] = 1;
        }
    }
    cout << max_flow(s,t) << '\n';
    
    // for (int i = 1; i <= n; i++)    {
    //     for (int j = 1; j <= n; j++)        cerr << f[i][j] << " ";
    //     cerr << '\n';
    // }
    
    dfs(s);
    
    for (int i = 1; i <= n; i++)        
        for (int j = 1; j <= n; j++) 
            if (f[i][j] && vis[i] && !vis[j])       
                cout << i << " " << j << '\n';
}


signed main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stderr);
    solve();
    return 0;
}
