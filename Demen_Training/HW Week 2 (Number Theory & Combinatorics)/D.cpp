#include<bits/stdc++.h>

using namespace std;

//#define int long long
#define fi first
#define se second
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

const int N = 1e5 + 5;
const ll INF = 2e18 + 5;
const int inf = 2e9 + 5;
const int mod = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}


void solve() {
    int n;  cin >> n;
    vi a(n + 1);
    vt<unordered_map<int, int>> dp(n + 1);
    for (int i = 1; i <= n; i++)        {cin >> a[i];   dp[i][a[i]] = 1;}
    
    // dp[i][gcd] = max size of subarray ending at i with GCD gcd
    // extend subarrays
    for (int i = 2; i <= n; i++)    {
        for (auto [_gcd, len] : dp[i - 1])  {
            int new_gcd = __gcd(_gcd, a[i]);
            dp[i][new_gcd] = max(dp[i][new_gcd], len + 1);
        }
    }
    
    // The answer for ans {len} will be the maximum {gcd} for which dp[i][gcd] = len
    vi ans(n + 1 , 0);
    for (int i = 1; i <= n; i++)   
        for (auto [_gcd, len] : dp[i])  
            ans[len] = max(ans[len], _gcd);
    
    for (int i = 1; i <= n; i++)    cout << ans[i] << ' ';
    cout << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    int test;   cin >> test;    
    while (test--)    solve();
    return 0;
}
