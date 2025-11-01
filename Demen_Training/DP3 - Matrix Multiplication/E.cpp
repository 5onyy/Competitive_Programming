// Solution: 
// Flatten the chess board
// mat[u][v] : number of ways to move from cell [u] to cell [v]
// we store all the answer from step k - 1 to mat[0][64]
// or sum: mat[0][i], 0 <= i <= 64 after take expo of k


#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// #define int unsigned int
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
using ull = unsigned int;
using ll = long long;
using ld = long double;
using vi = vt<int>;
using ii = pair<int, int>;
using iii = pair<int, ii>;
using vii = vt<ii>;

const ll INF = 1e18 + 5;
const int inf = 2e9 + 5;
const int mod = 1e9 + 7;
const int td[8] = {-2, -2, -1, -1, 1, 1, 2, 2}, tc[8] = {-1, 1, 2, -2, 2, -2, -1, 1};
template<typename T> using minpq = priority_queue<T, vt<T>, greater<T>>;
template<typename T> using maxpq = priority_queue<T>;
template<class T>	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll fpow(ll a, ll b, const ll c) { ll ans = 1; a %= c; for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c; return ans;}
ll fpow(ll a, ll b) {ll ans = 1; for (; b; b >>= 1, a *= a) if (b & 1) ans *= a; return ans;}

const int N = 65;

struct Matrix {
    ull mat[N][N];
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
        // ans.mat[i][j] %= MOD;
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

bool inside(int i, int j) {
    return (i >= 0 && i < 8 && j >= 0 && j < 8);
}

void solve() {
    int k;  cin >> k;
    Matrix state;
    for (int i = 0; i < 8; i++) {        
        for (int j = 0; j < 8; j++) {
            int u_id = i * 8 + j;
            for (int t = 0; t < 8; t++) {
                int ii = i + td[t];
                int jj = j + tc[t];
                if (!inside(ii,jj)) continue;
                int v_id = ii * 8 + jj;
                //cerr << u_id << ' ' << v_id << '\n';
                state.mat[u_id][v_id] = 1;
            }
        }
    }
    // Phai noi dinh 64->64 de khi nhan ma tran se luon ton tai duong di u->64->64: de luu step k - 1
    for (int i = 0; i <= 64; i++)   state.mat[i][64] = 1;
    
    // C1:
    // Matrix ans = epow(state, k);
    // ull res = 0;
    // for (int i = 0; i < N; i++)     res += ans.mat[0][i];
    // cout << res;
    
    // C2: 
    // take the initial graph
    // From every vertex add an edge to a fake vertex N+1;
    // Add an edge from N+1 to N+1, for case k = 1, we just move from 0 to 64 and 64 to 64 (we dont make any move)
    // Every path of len k equals to initial graph of len (k + 1) ending at vertex N + 1
    // graph of len (k + 1) equals to epow(matrix, k + 1)

    
    Matrix ans = epow(state, k + 1);
    cout << ans.mat[0][64]; // total dp of step k
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
