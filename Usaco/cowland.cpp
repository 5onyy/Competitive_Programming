#include<bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define sz(x) (int)(x).size()
#define sqr(x) ((x) * (x))
#define log2i(x) (64 - __builtin_clzll(1ll * (x)) - 1)
#define all(x)         x.begin(),x.end()
#define rall(x)        x.rbegin(),x.rend()
#define debug(x) { cout << #x << " = "; cout << (x) << endl; }
#define rr(x)          sort(all(x)),x.resize((unique(all(x))-x.begin()));
#define rep(i, a, b) for (int i = a; i < (b); ++i)

template<typename T> using vt = vector<T>;
using ll = long long;
using ld = long double;
using vi = vt<int>;
using ii = pair<int, int>;
using vii = vt<ii>;

const ll INF = 4e18;
const int inf = INT_MAX;
const int MOD = 1000000003;
const int d4i[4] = { -1, 0, 1, 0}, d4j[4] = {0, 1, 0, -1};
const int d8i[8] = { -1, -1, 0, 1, 1, 1, 0, -1}, d8j[8] = {0, 1, 1, 1, 0, -1, -1, -1};

template<class U, class V> std::ostream& operator << (std::ostream& out, const std::pair<U, V>& p) {return out << '(' << p.first << ", " << p.second << ')';}   //cout pair type
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;

ll fgcd(ll a, ll b) {while (b) swap(b, a %= b); return a;}
ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}
int flog(int x) {return 31 - __builtin_clz(x);}
int flog(ll x) {return 63 - __builtin_clzll(x);}

void setIO(string name) {
	cin.tie(0)->sync_with_stdio(0);
	if (sz(name)) {
		freopen((name + ".in").c_str(), "r", stdin);
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

int n, q, timer;
vt<vi> a;
vi st, en;

void dfs(int u, int par = -1) {
	st[u] = timer++;
	for (int v : a[u])
		if (v != par)	dfs(v, u);
	en[u] = timer;
}

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j, 0, sz(jmp[k]))
			jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return in f i f a == b
		int dep = flog(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

// need to be accompanied with rmq
struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;
	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
				path.push_back(v), ret.push_back(time[v]);
				dfs(C, y, v);
			}
	}
	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
//d is t (a , b){return depth [a ] + depth [ b ] − 2∗depth [ lca (a , b) ] ;}
};

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a [ pos ] ^= d i f
		for (; pos < sz(s); pos |= pos + 1) s[pos] ^= dif;
	}
	ll query(int pos) { // sum of values in [0 , pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res ^= s[pos - 1];
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

int main() {
	setIO("cowland");
	cin >> n >> q;
	vi vals(n);
	st.resize(n);	en.resize(n);
	a.resize(n, vi());
	for (auto &x : vals)	cin >> x;
	for (int i = 0; i < n - 1; i++) {
		int u, v;	cin >> u >> v;	u--;	v--;
		a[u].pb(v);	a[v].pb(u);
	}
	FT fenwick(n);
	dfs(0);
	for (int i = 0; i < n; i++)	{
		fenwick.update(st[i], vals[i]);
		fenwick.update(en[i], vals[i]);
	}
	LCA lca(a);
	while (q--) {
		int typ;	cin >> typ;
		if (typ == 1) {
			int i, v;	cin >> i >> v;	i--;
			fenwick.update(st[i], vals[i]);
			fenwick.update(en[i], vals[i]);
			vals[i] = v;
			fenwick.update(st[i], v);
			fenwick.update(en[i], v);
		}
		else {
			int u, v;	cin >> u >> v;	u--;	v--;
			int w = lca.lca(u, v);
			int ans = fenwick.query(st[u] + 1) ^ fenwick.query(st[v] + 1) ^ vals[w];	//st[u] + 1  because fenwick only alow to compute in range [0,pos)
			cout << ans << '\n';
		}
	}
}