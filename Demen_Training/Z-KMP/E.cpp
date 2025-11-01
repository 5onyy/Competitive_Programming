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

const int N = 1e5 + 5;
const ll INF = 1e18 + 5;
const int inf = 2e9 + 5;
const int MOD = 1e9 + 7;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

struct FT
{
    int n;
    vi fen;
    FT() = default;
    FT(int _n) : n(_n), fen(_n) {}
    void update(int pos, int val)   {
        for (; pos <= n; pos += pos & -pos)     fen[pos] += val;
    }
    int get(int pos) {
        int ans = 0;
        for (; pos >= 1; pos -= pos & -pos)     ans += fen[pos];
        return ans;
    }
    void update(int l, int r, int val)       {
        if (r < l)      return;
        update(l, val);
        update(r + 1, -val);
    }
}fen;


vi zFunc(string s) {
    int n = sz(s);
    vi z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)      z[i] = min(z[i-l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])      z[i]++;
        if (r < i + z[i] - 1)   l = i, r = i + z[i] - 1;
        fen.update(1, z[i], 1);
    }
    return z;
}

void solve() {
    string s;   cin >> s;
    int n = sz(s);
    fen = FT(n + 5);
    vi z = zFunc(s);
    // for (int i : z)     cerr << i << ' ';   cerr << endl;
    vii ans;
    for (int L = 1; L < n; L++) {
        if (z[n - L] == L)  {   // prefix == suffix
            ans.pb({L, fen.get(L) + 1});
        }
    }
    ans.pb({n,1});
    cout << sz(ans) << '\n';
    for (auto xx : ans)  {
        cout << xx.f << " " << xx.s << '\n';
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
