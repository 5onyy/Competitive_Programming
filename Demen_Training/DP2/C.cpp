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

const int N = 20;

struct node {
    int last;
    int rides;
    // We define two functions: rides(S) is the minimum number of rides for a subset S, and last(S) is the minimum weight of the last ride. For example
    node() = default;
    node(int _rides, int _last) : last(_last), rides(_rides) {};
    node minimize(node a) {
        if (last > a.last)  return a;
        if (rides > a.rides)    return a;
        return node(rides, last);
    }
}dp[1 << N];

void solve() {
    int n, w;   cin >> n >> w;
    vi weight(n);
    for (int i = 0; i < n; i++)     cin >> weight[i];
    dp[0] = node(1,0);
    for (int msk = 1; msk < (1 << n); msk++) {
        dp[msk] = node(n + 1, 0);
        for (int i = 0; i < n; i++) {
            if (!(msk & (1 << i)))  continue;
            node prev_state = dp[msk ^ (1 << i)];
            if (prev_state.last + weight[i] <= w)   prev_state.last += weight[i];
            else prev_state.rides++, prev_state.last = weight[i];
            dp[msk] = dp[msk].minimize(prev_state);
        }
    }
    cout << dp[(1 << n) - 1].rides;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
