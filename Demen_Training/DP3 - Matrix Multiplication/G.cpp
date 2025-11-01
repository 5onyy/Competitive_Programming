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

const int N = 13;
int n, k;   

struct Matrix {
    int mat[N][N];
    Matrix() {memset(mat, 0, sizeof mat);}
    Matrix I() {
        Matrix ans;
        for (int i = 0; i < N; i++)    ans.mat[i][i] = 1;
        return ans;
    }
};

Matrix matMul(Matrix a, Matrix b) { // O(N^3)
    Matrix ans;
    for (int i = 0; i < N; i++)     for (int j = 0; j < N; j++)
    for (int k = 0; k < N; k++) {
        ans.mat[i][j] += a.mat[i][k] * b.mat[k][j];
        ans.mat[i][j] %= mod;
    }
    return ans;
}

Matrix epow(Matrix a, int n) {
    Matrix ans;
    if (n == 0) return ans.I();
    if (n == 1) return a;
    if (n % 2 == 0)     {
        Matrix t = epow(a, n / 2);
        return matMul(t, t);
    } 
    else {
        Matrix t = epow(a, n / 2);
        return matMul(matMul(t,t),a);
    }
}

void solve() {
    cin >> n >> k;
    vi a(n), c(n + 1);
    Matrix state;
    for (int i = 0; i < n; i++)     cin >> a[i];
    if (k < n)  return void(cout << a[k]);
    reverse(all(a));
    
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        state.mat[0][i - 1] = c[i];
    }
    int p,q,r;  cin >> p >> q >> r;
    a.pb(1);    a.pb(n);    a.pb(n * n);
    
    // Constrct matrix state
    state.mat[0][n] = p, state.mat[0][n + 1] = q, state.mat[0][n + 2] = r;
    
    for (int i = 1; i < n; i++) state.mat[i][i - 1] = 1;
    
    state.mat[n][n] = 1;
    
    state.mat[n + 1][n] = state.mat[n + 1][n + 1] = 1;
    
    state.mat[n + 2][n] = 1, state.mat[n + 2][n + 1] = 2, state.mat[n + 2][n + 2] = 1;
    
    // solve
    Matrix ans = epow(state, k - n + 1);

    int res = 0;
    for (int i = 0; i < n + 3; i++) {
        res += ans.mat[0][i] * a[i];
        res %= mod;
    }
    cout << res;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
