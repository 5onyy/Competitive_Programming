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

const int N = 2e5 + 5;

struct Node {
    int prefix, suffix, sum, mx;
    Node() {};
    Node(int pref, int suf, int _sum, int _mx) {
        prefix = pref;
        suffix = suf;
        sum = _sum;
        mx = _mx;
    }
}seg[4 * N];

Node combine(Node u, Node v) {
    int prefix = max(v.prefix + u.sum, u.prefix);
    int suffix = max(v.sum + u.suffix, v.suffix);
    int sum = u.sum + v.sum;
    int mx = max(v.mx, max(u.mx, v.prefix + u.suffix));
    return Node(prefix, suffix, sum, mx);
}

void update(int id, int l, int r, int pos, int val) {
    if (l == r) {
        seg[id] = Node(max(val,0LL), max(0LL, val), val, max(0LL, val));
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)     update(id * 2, l, mid, pos, val);
    else update(id * 2 + 1, mid + 1, r, pos, val);
    seg[id] = combine(seg[id * 2], seg[id * 2 + 1]);
}

int a[N];

void solve() {
    int n,q;    cin >> n >> q;
    for (int i = 1; i <= n; i++)    {
        cin >> a[i];    update(1,1,n,i,a[i]);
    }
    while (q--) {
        int pos, val;   cin >> pos >> val;
        update(1,1,n,pos,val);
        a[pos] = val;
        cout << max(seg[1].mx,0LL) << '\n';
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
