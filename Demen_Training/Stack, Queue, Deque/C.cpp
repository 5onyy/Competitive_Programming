// Problem https://cses.fi/problemset/task/1147

// idea:

// 4 7
// ...*.*.
// .*.....
// .......
// ......*

// can modelize as:

// i = 1:  4 1 4 0 4 0 3
// i = 2:  3 0 3 3 3 3 2
// i = 3:  2 2 2 2 2 2 1
// i = 4:  1 1 1 1 1 1 0

// We try to fix the top of the rectangle, then solve like https://cses.fi/problemset/task/1142


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

const int N = 1e3 + 5;
int a[N][N];
queue<int>  col[N];

void solve() {
    int n, m;  cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            if (c == '*')   col[j].push(i);
        }
    }
    for (int j = 1; j <= m; j++)    col[j].push(n + 1);
    for (int i = 1; i <= n; i++) {    
        for (int j = 1; j <= m; j++)    if (col[j].front() < i)     col[j].pop();
        for (int j = 1; j <= m; j++)    a[i][j] = col[j].front() - i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        stack <ii> st;
        for (int j = 1; j <= m; j++) {
            int start = j;
            while (sz(st) && a[i][j] < st.top().se) {
                auto [last_idx, hi] = st.top();     st.pop();
                start = last_idx;
                ans = max(ans, hi * (j - last_idx));
            }
            st.push({start, a[i][j]});
        }
        while (sz(st)) {
            auto [last_idx, hi] = st.top();     st.pop();
            ans = max(ans, (m + 1 - last_idx) * hi);
        }
        // cout << ans << ' ';
    }
    
    cout << ans << '\n';
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
