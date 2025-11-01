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

/*-------------------------------FOR DEBUGGING --------------------------------------*/
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define db(x) { std::cerr << "[" << #x << " = "; std::cerr << (x) << "] "; }
#define debug(x) { std::cerr << "[" << #x << " = "; std::cerr << (x) << "] " << endl; }

// For printing std::pair, container, etc.
template<class U, class V> std::ostream& operator << (std::ostream& out, const std::pair<U, V>& p) {
    return out << '(' << p.first << ", " << p.second << ')';
}

template<class Con, class = decltype(begin
(std::declval<Con>()))>
typename std::enable_if < !std::is_same<Con, std::string>::value, std::ostream& >::type
operator << (std::ostream& out, const Con& con) {
    out << '{';
    for (auto beg = con.begin(), it = beg; it != con.end(); it++) {
        out << (it == beg ? "" : ", ") << *it;
    }
    return out << '}';
}
template<size_t i, class T> std::ostream& print_tuple_utils(std::ostream& out, const T& tup) {
    if (i == std::tuple_size<T>::value) return out << ")";
    else return print_tuple_utils < i + 1, T > (out << (i ? ", " : "(") << get<i>(tup), tup);
}
template<class ...U> std::ostream& operator << (std::ostream& out, const std::tuple<U...>& t) {
    return print_tuple_utils<0, std::tuple<U...>>(out, t);
}
/*-----------------------------------------------------------------------------------*/

unordered_map<int, int> mp;

struct FT {
    vi v;
    int n;
    FT(int _n) : n(_n) {v.assign(n + 1, 0);};
    void update(int pos, int val) {
        for (; pos <= n; pos += pos & -pos)     v[pos] += val;
    }
    int get(int u) { // 1..u
        int sum = 0;
        for (; u >= 1; u -= u & -u) sum += v[u];
        return sum;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
    int lowerbound(int k){
        int pos = 0, sum = 0;
        for(int p = 20; p >= 0; --p){
            if ((pos | (1 << p)) <= n && sum + v[pos | (1 << p)] < k){
                pos |= (1 << p);
                sum += v[pos];
            }
        }
        return pos + 1;
    }
    
};

void solve() {
    int q;  cin >> q;
    vt<pair<char, int>>   queries;
    vi values;
    for (int i = 1; i <= q; i++)    {
        char typ;   int x;  cin >> typ >> x;
        if (typ != 'K') values.pb(x);
        queries.pb({typ, x});
    }
    rr(values);
    // debug(values);
    int n = 0;    
    for (int i : values)  mp[i] = ++n;
    // for (int i = 0; i < sz(values); i++)    cerr << mp[values[i]] << ' ';
    // cerr << '\n';
    vi a(n + 1);
    FT fen(n);
    for (int i = 0; i < q; i++) {
        auto [typ, x] = queries[i];
        if (typ == 'I') {
            int pos = mp[x];
            if (a[pos] == 0)    {
                fen.update(pos, 1);
                a[pos] = 1;
                // cerr << typ << ' '; debug(a);
            }
        }
        if (typ == 'D') {
            int pos = mp[x];
            if (a[pos] == 1) {
                fen.update(pos, -1);
                a[pos] = 0;
                // cerr << typ << ' '; debug(a);
            }
        }
        if (typ == 'K') {
            if (x > fen.get(n))  cout << "invalid" << '\n';
            else {
                int vt = fen.lowerbound(x);
                // cerr << typ << ' ' << vt << '\n';
                cout << values[vt - 1] << '\n';
            }
        }
        if (typ == 'C') {
            int pos = mp[x];
            cout << fen.get(pos - 1) << '\n';
            // cerr << typ << ' ' << pos << '\n';
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
