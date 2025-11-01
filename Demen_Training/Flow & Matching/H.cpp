//no 3 vertex - cycle => DAG
//if A -> B, B -> C then A -> C => Transitive Closure 
//=> Maximum Independent Set == Minimum Path Cover
// Minimum Path Cover = n - Maximum Bipartie Matching
// Minimum vertex cover of  DAG == Maximum Bipartie Matching
#include<bits/stdc++.h>

using namespace std;

#define pb push_back

using ll = long long;
using ii = pair<int, int>;
using iii = pair<int, ii>;

const int N = 1005;
const ll INF = numeric_limits<long long>::max() / 2;
const int MOD = 1e9 + 7;

vector<int> adj[N];
vector<int> lst;

bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa, vector<int>& A, vector<int>& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
	int res = 0;
	vector<int> A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(A.begin(), A.end(), 0);
		fill(B.begin(), B.end(), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		for (int a = 0; a < g.size(); a++) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
        for (int a = 0; a < g.size(); a++)
			res += dfs(a, 0, g, btoa, A, B);
	}
}

void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int> ());
    for (int i = 1; i <= m; i++) {
        int u,v;
        cin >> u >> v;
        g[u].pb(v);
    }
    vector<int> btoa(n + 1, -1);
    cout << n - hopcroftKarp(g,btoa);
    
}

signed main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
