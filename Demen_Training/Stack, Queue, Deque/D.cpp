// idea: 
// For each i, we know that ai can be minimum element in groups of size 1, 2, ..., ri - li - 1. start at i
// l_i = max {pos} so that a[i] > a[pos], pos < i
// r_i = min {pos} so that a[i] > a[pos], pos > i
// ans_len = max(ans_len, (min element of group size {len} start at {1 <= i <= n - i + 1} ) )

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

void solve() {
    int n;  cin >> n;
    vi l(n + 1), r(n + 1), a(n + 1), ans(n + 1, 0);
    for (int i = 1; i <= n; i++)        cin >> a[i];
    stack<int> st;
    for (int i = 1; i <= n; i++)    {
        while (sz(st) && a[st.top()] >= a[i])   st.pop();
        if (st.empty()) l[i] = 0;
        else l[i] = st.top();
        st.push(i);
    }
    while (sz(st))  st.pop();
    for (int i = n; i >= 1; i--) {
        while (sz(st) && a[st.top()] >= a[i])   st.pop();
        if (st.empty())     r[i] = n + 1;
        else r[i] = st.top();
        st.push(i);
    }
    
    // for (int i = 1; i <= n; i++)    cout << l[i] << ' ';
    // cout << '\n';
    // for (int i = 1; i <= n; i++)    cout << r[i] << ' ';
    // cout << '\n';
    for (int i = 1; i <= n; i++) {
        int len = r[i] - l[i] - 1;
        ans[len] = max(ans[len], a[i]);
    }
    for (int i = n - 1; i >= 1; i--) ans[i] = max(ans[i], ans[i + 1]);
    for (int i = 1; i <= n; i++)         cout << ans[i] << ' ';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
