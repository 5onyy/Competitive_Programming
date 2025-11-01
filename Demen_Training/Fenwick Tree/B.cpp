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

const int N = 1e5 + 5;
int seg[4 * N];


void update(int id, int u, int l, int r, int val) {
    // cerr << l << ' ' << r << '\n';
    if (l == r)   {
        if (u == l)        seg[id] = val;   
        return;
    }
    int mid = (l + r) / 2;
    if (u <= mid)   update(id * 2, u, l, mid, val);
    else update(id * 2 + 1, u, mid + 1, r , val);
    
    seg[id] = max(seg[id * 2], seg[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (r < u || l > v) return -INF;
    if (l >= u && r <= v)   return seg[id];
    int mid = (l + r) / 2;
    return max(get(id * 2, l, mid, u , v) , get(id * 2 + 1, mid + 1, r, u, v));
}

void solve() {
    int n, q;   cin >> n;
    for (int i = 1; i <= n; i++){
        int x;  cin >> x;
        update(1, i, 1, n, x);
    }
    cin >> q;
    while (q--) {
        int typ;    cin >> typ;
        if (typ == 1) {
            int pos, val;   cin >> pos >> val;
            update(1, pos, 1, n, val);
        }
        else {
            int l, r;   cin >> l >> r;
            cout << get(1, 1, n, l, r) << '\n';
        }
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
