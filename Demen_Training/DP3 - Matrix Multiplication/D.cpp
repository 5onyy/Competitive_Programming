// Solution: https://www.youtube.com/watch?v=kQuCOFzWoa0

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

const int N = 101;
const int MOD = 1e9 + 7;

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
        ans.mat[i][j] %= MOD;
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
    int n,m,k;  cin >> n >> m >> k;
    Matrix dp;
    // (dp[u][v]) ^ k : number of path from u -> v consisting of k-step
    // In this type of problem, we can let base case of dp[u][v] by adjacent matrix
    for (int i = 1; i <= m; i++) {
        int u,v;    cin >> u >> v;  
        u--;    v--;
        dp.mat[u][v] = 1;
    }
    dp = epow(dp, k);
    int ans = 0;
    for (int i = 0; i < n; i++)     for (int j = 0; j < n; j++)     ans += dp.mat[i][j],    ans %= MOD;
    cout << ans;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
