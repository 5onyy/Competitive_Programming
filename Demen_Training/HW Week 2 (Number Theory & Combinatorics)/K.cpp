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

const int N = 1e6 + 5;
int fact[N], inv_fact[N];

int inv(int x) {return fpow(x, mod - 2, mod);}

void preprocess() {
    fact[0] = 1;
    for (int i = 1; i <= 1e6; i++)  fact[i] = fact[i - 1] * i % mod;
    inv_fact[(int) 1e6] = inv(fact[(int) 1e6]);
    for (int i = 1e6 - 1; i >= 0; i--)  inv_fact[i] = (i + 1) * inv_fact[i + 1] % mod;
}

int C(int n, int k) {if (n == 0)    return 0; return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;}

void solve() {
    int n, k;   cin >> n >> k;
    cout << C(n, k) << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    preprocess();
    int test;   cin >> test;
    while (test--)    solve();
    return 0;
}
