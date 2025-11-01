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
int flog(int x) {return 31 - __builtin_clz(x);}
int flog(ll x) {return 63 - __builtin_clzll(x);}

void setIO(string name) {
	cin.tie(0)->sync_with_stdio(0);
	if (sz(name)) {
		freopen((name + ".inp").c_str(), "r", stdin);
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

#define int long long

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int n;
vt<vi> a;
int dp[N][2];

void dfs(int u, int par = -1) {
	for (int v : a[u]) {
		if (v == par)	continue;
		dfs(v, u);
		dp[u][0] = (dp[u][0] * dp[v][1]) % mod;
		dp[u][1] = (dp[u][1] * (dp[v][0] + dp[v][1])) % mod;
	}
}

signed main() {
	setIO("");
	cin >> n;
	//if (n == 1)	{cout << 2;	return 0;}
	a.resize(n + 1);
	for (int i = 1; i <= n; i++)	{dp[i][0] = 1; 	dp[i][1] = 1;}
	for (int i = 1; i < n; i++) {
		int u, v;	cin >> u >> v;
		a[u].pb(v);	a[v].pb(u);
	}
	dfs(1);
	/*	for (int i = 1; i <= n; i++) {
			cout << dp[i][0] << ' ' << dp[i][1] << '\n';
		}*/
	cout << (dp[1][0] + dp[1][1]) % mod;
}

