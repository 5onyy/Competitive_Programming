// Maximum flow from s to t in a flow network. O(E^2*V)
// Tested: https://oj.vnoi.info/problem/nkflow

#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 500;
const int INF = numeric_limits<long long>::max() / 2;
int c[N][N], par[N], f[N][N], d[N], cost[N][N];
int n,m,s,t;

int bfs(int s, int t) {
    queue<int> q;
    fill(par, par + N, -1);
    fill(d, d + N, 0);
    q.push(s);  d[s] = INF;
    while (!q.empty()) {
        int u = q.front();      q.pop();
        for (int i = 0; i <= 2*n+1; i++) {
            if (c[u][i] - f[u][i] > 0 && par[i] == -1) {
                //cerr << u << " -> " << i << endl;
                d[i] = min(d[u], c[u][i] - f[u][i]);
                par[i] = u;     q.push(i);
                if (i == t)     return d[t];
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int cur = 0, ans = 0;
    while ((cur = bfs(s,t)) > 0) {
        ans += cur;
        int v = t;
        while (v != s) {
            f[par[v]][v] += cur;
            f[v][par[v]] -= cur;
            v = par[v];
        }
    }
    return ans;
}

signed main() {
    cin >> n;
    int lo = INF,hi= -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int C;
            cin >> C;
            cost[i][j] = C;
            hi = max(hi, C);
            lo = min(lo, C);
        }
    }    
    int res = 0;
    while (lo <= hi) {
        memset(f,0,sizeof f);
        memset(c,0,sizeof c);
        for (int i = 1; i <= n; i++) {
            c[0][i] = 1;
            c[i + n][2*n+1] = 1;
        }
        int mid = (lo + hi) / 2;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (cost[i][j] <= mid) {
                    c[i][j + n] = 1;
                    //cerr << i << "->" << j << ": " << c[i][j + n] << endl;
                }
            }
        }
        int cur = max_flow(0, 2*n+1);
        // cerr << mid  <<" -> " << cur << endl << endl;
        if (cur == n)        res = mid, hi = mid - 1;
        else if (cur < n) lo = mid + 1;
        else hi = mid - 1;
    }
    cout << res;
    return 0;
}