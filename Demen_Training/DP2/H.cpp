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

int dp[16][2];

int calc(int n) {
    for (int i = 0; i < 16; i++)    for (int j = 0; j <= 1; j ++)   dp[i][j] = 0;
    if (n == -1) return 0;
    string t = to_string(n);
    for (int i = 0; i < sz(t); i++) {
        for (int lower = 0; lower <= 1; lower++) {
            for (int digit = 0; digit <= 9; digit++) {
                if (lower == 0 && digit > (t[i] - '0')) break;
                int nLower = lower | (digit < (t[i] - '0'));
                // cerr << i << ' ' << digit << ' ' << lower << ' ' << nLower << '\n';
                dp[i + 1][nLower] += dp[i][lower] + digit;
            }    
        }
        // cerr << '\n';
    }
    // for (int i = 0; i < 10; i++)    cerr << dp[1][1] << ' ';
    return dp[sz(t) - 1][1] + dp[sz(t) - 1][0] ;
}

void solve() {
    int a, b;   cin >> a >> b;
    cout << calc(b) - calc(a - 1) << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    int test;   cin >> test;
    while (test--)    solve();
    return 0;
}
