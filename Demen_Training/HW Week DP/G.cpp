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

const int N = 505;
int dp[N][N], C[N][N];

void solve() {
    string s;   cin >> s;
    int n = sz(s);
    s = "#" + s;
    C[0][0] = 1;
    for (int i = 1; i < N; i++)    {
        C[i][0] = 1;
        for (int j = 1; j < N; j++)    C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
    for (int i = 0; i <= n; i++)    dp[i + 1][i] = 1;
    for (int len = 2; len <= n; len+=2) {
        for (int i = 1, j = len; j <= n; i++, j++) {
            for (int k = i + 1; k <= j; k+=2) {
                if (s[i] == s[k])   {
                    dp[i][j] = (dp[i][j] + (dp[i + 1][k - 1] * dp[k + 1][j]) % MOD * C[(j - i + 1) / 2][(k - i + 1) / 2] % MOD) % MOD;
                }
            }
        }
    }
    cout << dp[1][n];
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
