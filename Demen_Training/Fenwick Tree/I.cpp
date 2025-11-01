#include<bits/stdc++.h>

using namespace std;

#define int long long
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

const ll INF = 2e18 + 5;
const int inf = 2e9 + 5;
const int mod = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

struct FT {
    int n;
    vi fen;
    FT (int _n) : n(_n), fen(n + 1) {};
    void update(int pos, int val)   {
        for (;pos <= n; pos += pos & -pos)   fen[pos] = (fen[pos] + val) % mod;
    }
    int get(int pos) {
        int sum = 0;
        for (; pos >= 1; pos -= pos & -pos)     sum += fen[pos],    sum %= mod;
        return sum;
    }
};

void solve() {
    int n;  cin >> n;
    vi a(n), b(n);
    for (int i = 0; i < n; i++)    {cin >> a[i];    b[i] = a[i];}
    rr(b);
    unordered_map <int, int> compress;
    int cnt = 0;
    for (int i : b)     compress[i] = ++cnt;
    FT fen(sz(b));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int compress_value = compress[a[i]];
        int tmp = (fen.get(compress_value - 1) + 1) % mod;
        ans += fen.get(compress_value - 1) + 1;
        ans %= mod;
        fen.update(compress_value, tmp);
        // cerr << compress_value << ' ' << ans << '\n';
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
