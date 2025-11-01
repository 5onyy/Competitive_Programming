#include<bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define sz(x) (int)(x).size()
#define sqr(x) ((x) * (x))
#define all(x)         x.begin(),x.end()
#define debug(x) { cout << #x << " = "; cout << (x) << endl; }
#define rr(x)          sort(all(x)),x.resize((unique(all(x))-x.begin()));
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define emb emplace_back
#define timer cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n"
#define int long long

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

// FOR DEBUGGING
template<class U, class V> std::ostream& operator << (std::ostream& out, const std::pair<U, V>& p) {return out << '(' << p.first << ", " << p.second << ')';}   //cout pair type
template<class Con, class = decltype(begin(std::declval<Con>()))>
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
/*-------------------------------------------------*/

ll fgcd(ll a, ll b) {while (b) swap(b, a %= b); return a;}
ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}
//int flog(int x) {return 31 - __builtin_clz(x);}
int flog(ll x) {return 63 - __builtin_clzll(x);}

void setIO(string name) {
	cin.tie(0)->sync_with_stdio(0);
	if (sz(name)) {
		freopen((name + ".inp").c_str(), "r", stdin);
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	int size() {return s.size();}
	void print() {debug(s);}
	void update(int pos, ll dif) { // a [ pos ] += d i f
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0 , pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
		return res;
	}
	int lower_bound(ll sum) {// min pos s t sum of [0 , pos ] >= sum
		// Returns n i f no sum is >= sum, or −1 i f empty sum is .
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
				pos += pw, sum -= s[pos - 1];
		}
		return pos;
	}
};

int n, q;
ll ans = 0;
vt<FT> DS;

void decode(int &l, int &r, ll &x, ll last) {
	l = (l + last - 1) % n + 1;
	r = (r + last - 1) % n + 1;
	x = (x + last - 1) % n + 1;
	if (l > r)	swap(l, r);
}

void decode(int &p, ll last) {
	p = (p + last - 1) % (n - 1) + 1;
}

signed main() {
	setIO("");
	cin >> n >> q;
	vi a(n + 5);
	vt<vi> pos(n + 5);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		pos[a[i]].pb(i);
	}
	DS.resize(n + 5, FT(0));
	for (int  i = 1; i <= n; i++) {
		DS[i] = FT(sz(pos[i]));
		for (int j = 0; j < sz(pos[i]); j++)	DS[i].update(j, pos[i][j]*pos[i][j]);
	}
	while (q--) {
		int typ;	cin >> typ;
		if (typ == 1) {
			int p;	cin >> p;
			decode(p, ans);
			if (p == n)	continue;
			if (a[p] == a[p + 1])	continue;
			int t1 = lower_bound(all(pos[a[p]]), p) - pos[a[p]].begin();
			int t2 = lower_bound(all(pos[a[p + 1]]), p + 1) - pos[a[p + 1]].begin();
			DS[a[p]].update(t1, sqr(p + 1) - sqr(pos[a[p]][t1]));
			DS[a[p + 1]].update(t2, sqr(p) - sqr(pos[ a[p + 1] ][t2]));
			swap(pos[a[p + 1]][t2], pos[a[p]][t1]);
			swap(a[p], a[p + 1]);
		}
		if (typ == 2) {
			int l, r;	ll x;	cin >> l >> r >> x;
			decode(l, r, x, ans);
			int lo = lower_bound(all(pos[x]), l) - pos[x].begin();
			int hi = upper_bound(all(pos[x]), r) - pos[x].begin();
			ans = DS[x].query(hi) - DS[x].query(lo);
			cout << ans << '\n';
		}
		if (typ == 3) {
			int l, r;	ll x;	cin >> l >> r >> x;
			decode(l, r, x, ans);
			ans = DS[x].query(r) - DS[x].query(l - 1);
			cout << ans << '\n';
		}
	}
}

