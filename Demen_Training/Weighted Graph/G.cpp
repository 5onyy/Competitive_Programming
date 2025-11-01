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

const int N = 2e5 + 5;
int n,m;
vii adj[N];

struct Node {
    int min_path, cnt_min, max_flight, min_flight;    
    Node() {
        min_path = INF;
        cnt_min = 0;
        max_flight = -INF;
        min_flight = INF;
    }
    Node(int min_path, int cnt_min, int max_flight, int min_flight) {
        this->min_path = min_path;
        this->cnt_min = cnt_min;
        this->max_flight = max_flight;
        this->min_flight = min_flight;
    }
}d[N];

void dijskstra(int s) {
    d[s] = Node(0,1,0,0);
    minpq<ii> pq;
    pq.push({0,s});
    while (sz(pq)) {
        auto [d_u,u] = pq.top();  pq.pop();
        if (d_u != d[u].min_path)       continue;
        for (auto [v,w] : adj[u]) {
            if (d[v].min_path > d[u].min_path + w) {
                d[v] = Node(d[u].min_path + w,
                        d[u].cnt_min,
                        d[u].max_flight + 1,
                        d[u].min_flight + 1);
                pq.push({d[v].min_path, v});
            }
            else if (d[v].min_path == d[u].min_path + w){
                d[v].cnt_min += d[u].cnt_min;
                d[v].cnt_min %= mod;
                d[v].min_flight = min(d[v].min_flight, d[u].min_flight + 1);
                d[v].max_flight = max(d[v].max_flight, d[u].max_flight + 1);
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u,v,w;  cin >> u >> v >> w;
        adj[u].pb({v,w});
    }
    dijskstra(1);
    cout << d[n].min_path << ' ' << d[n].cnt_min << ' ' << d[n].min_flight << ' ' << d[n].max_flight;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
