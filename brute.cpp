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

const int N = 2e5 + 5;
const ll INF = numeric_limits<long long>::max() / 2;
const int MOD = 1e9 + 7;

template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

void solve() {
    int n;
    cin >> n;
    int ans = -INF;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ans = max(ans, x);
    }
    cout << ans;
}


signed main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
