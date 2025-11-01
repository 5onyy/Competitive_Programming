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

int h,a,b,c;
int d[100005];  // =d[i] = x_min, x % a = i

void dijsktra() {
    minpq<ii> pq;
    for (int i = 0; i < a; i++)     d[i] = INF;
    pq.push({0,0});
    d[0] = 0;
    while (sz(pq)) {
        auto [d_u,u] = pq.top();    pq.pop();
        if (d_u != d[u])   continue;
        for (auto [v, w] : {ii((u + b) % a, b), ii((u + c) % a, c)}) {
            if (d[v] > d[u] + w)    d[v] = d[u] + w,    pq.push({d[v], v});
        }
    }
}

void solve() {
    cin >> h >> a >> b >> c;
    h--;
    if (a < b)  swap(a,b);
    if (a < c)  swap(a,c);
    dijsktra();
    int ans = 0;
    // for (int i = 0; i < a; i++)     cerr << d[i] << ' ';
    // cerr << '\n';
    for (int i = 0; i < a; i++) {
        if (h >= d[i]) {
            ans += (h - d[i]) / a + 1;
        }
    }
    cout << ans;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
