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

int n, k, N;
vi fact, inv_fact;

void preprocess(){
    fact.resize(N + 1), inv_fact.resize(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++)    fact[i] = i * fact[i - 1] % mod;
    inv_fact[N] = fpow(fact[N], mod - 2, mod);
    for (int i = N - 1; i >= 0; i--)    inv_fact[i] = (i + 1) * inv_fact[i + 1] % mod;
}

int C(int n, int k) {
    return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}

void solve() {
    cin >> n >> k;
    N = n + k - 1;
    preprocess();
    cout << C(N, k);
} 

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
