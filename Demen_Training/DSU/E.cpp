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

const int N = 3e5 + 5;
int next_alive[N], ans[N];

int get(int x) {
    if (next_alive[x] != x)      next_alive[x] = get(next_alive[x]);
    return next_alive[x];
}

void tournament(int l, int r, int x) {
    if (l > r)  return;
    while (get(l) <= r) {
        l = get(l);
        ans[l] = x;
        next_alive[l] = l + 1;
    }
}

void query(int l, int r, int x) {
    tournament(l,r,x);
}

void solve() {
    int n,q;    cin >> n >> q;
    for (int i = 1; i <= n + 1; i++) {
        next_alive[i] = i;
    }
    vector<array<int,3>> queries(q);
    for (int i = 0; i < q; i++){
        cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
    }
    for (int i = q - 1; i >= 0; i--)    {
        query(queries[i][0],queries[i][1],queries[i][2]);
    }
    for (int i = 1; i <= n; i++)    cout << ans[i] << '\n' ;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
