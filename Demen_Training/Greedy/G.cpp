#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

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

const ll INF = 4e18;
const int inf = INT_MAX;
const int td[8] = { -1, 0, 1, 0, -1, -1, 1, 1}, tc[8] = {0, 1, 0, -1, -1, 1, 1, -1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;

ll fgcd(ll a, ll b) {while (b) swap(b, a %= b); return a;}
ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}
int flog(ll x) {return 63 - __builtin_clzll(x);}    //for integer : 31 - __builin_clz(x);

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    
    Tree<ii> s;
    int n;  cin >> n;
    vt<iii> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi >> a[i].se.fi;
        a[i].se.se = i;
    }
    sort(all(a));
    vi ans(n);
    int cnt = 0;
    s.insert({a[0].se.fi, 0}),   ans[a[0].se.se] = 0;
    for (int i = 1; i < n; i++) {
        ii p = *s.begin();
        if (p.fi >= a[i].fi) {
            cnt++;
            s.insert({a[i].se.fi,cnt});  
            ans[a[i].se.se] = cnt;
        }
        else {
            s.erase(*s.begin());
            s.insert({a[i].se.fi, p.se});
            ans[a[i].se.se] = p.se;
        }
    }
    cout << cnt + 1 << '\n';
    for (int i : ans)   cout << i + 1 << ' ';
}