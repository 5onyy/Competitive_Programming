// source: https://cses.fi/problemset/task/1082

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

const int MOD = 1e9 + 7;
const ll INF = 4e18;
const int inf = INT_MAX;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;

ll fgcd(ll a, ll b) {while (b) swap(b, a %= b); return a;}
ll fpow(ll a, ll b, const ll c = MOD) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}
int flog(ll x) {return 63 - __builtin_clzll(x);}    //for integer : 31 - __builin_clz(x);

void add(int &x, int val) {
    x = (x + val) % MOD;
}

void mul(int &x, int val) {
    x = ((x % MOD) * (val % MOD)) % MOD;
}

void calc(int &s, int val, int start, int stop) {
    // n * d_0 * 1/2
    int amount = stop - start + 1;
    add (start, stop);
    mul(start, amount);
    mul(start, fpow(2, MOD - 2, MOD));
    mul(val, start);
    add(s, val);
}

void solve() {
    int n;  cin >> n;
    // define f(i) = floor(f/i), for each i <= n
    // The number of distinct f(i) <= 2 * sqrt(n) (https://math.stackexchange.com/questions/1069460)
    // we jump i until we find f(i) that different from the previous f(i)
    int ans = 0;
    for (int  i = 1; i <= n;) {  // current number upto n
        int f_i = n / i;    
        int last_same = n / f_i;    // The last number j that has the same f(j) with i;
        calc(ans, f_i, i, last_same);
        i = last_same + 1;
    }
    cout << ans << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    solve();
}