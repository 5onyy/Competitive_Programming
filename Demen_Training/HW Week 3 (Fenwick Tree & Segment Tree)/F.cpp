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

struct FT {
    int n;
    vi fen;
    FT (int _n): n(_n), fen(n + 1, 0) {};
    void reset() {
        fen.clear();
        fen.assign(n + 1, 0);
    }
    void update(int pos, int val) {
        for (; pos <= n; pos += pos & -pos)     fen[pos] += val;
    }
    
    int get(int pos) {
        int sum = 0;
        for (; pos >= 1; pos -= pos & -pos)    sum += fen[pos];
        return sum;
    }
    
    int get(int l, int r) {
        if (r < l)  return 0;
        return get(r) - get(l - 1);
    }
};


const int N = 1e5 + 5;
int dp[4][N];

void solve() {
    int n;  cin >> n;
    vi a(n + 1);
    for (int i = 1; i <= n; i++)     {
        cin >> a[i];    
        dp[1][i] = 1;
    }
    int k =3;
    FT fen(n);
    for (int len = 2; len <= k; len++) {
        fen.reset();
        for (int i = 1; i <= n; i++)  {
            int tmp = fen.get(a[i] + 1, n);
            // cerr << tmp << ' ';
            dp[len][i] += tmp;
            fen.update(a[i], dp[len - 1][i]);
        }
        // cerr << '\n';
    }
    int ans = 0;
    // for (int len = 1; len <= 3; len++) {
    //     for (int i = 1; i <= n; i++)    cout << dp[len][i];
    //     cout << '\n';
    // }
    for (int i = 1; i <= n; i++)    ans += dp[k][i];
    cout << ans;
}

// 3 2 3 3 3 1

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
