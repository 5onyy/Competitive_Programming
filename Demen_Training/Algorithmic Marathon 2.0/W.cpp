#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n,m,dfsTime,numBridge;    
vector<int> adj[N];
vector<pair<int,int>> bridges; // All edges that are bridges
int num[N], low[N], tail[N], joint[N];

void dfs(int u, int par = -1) {
    int numChild = 0;
    num[u] = low[u] = ++dfsTime;
    for (int v : adj[u]) {
        if (v == par)   continue;
        if (!num[v]) {
            dfs(v,u);
            low[u] = min(low[u], low[v]);
            if (low[v] == num[v])   {
                bridges.push_back({u,v});
                numBridge++;
            }
            numChild++;
            if (par == -1 && numChild > 1)     joint[u] = 1;
            if (par != -1 && low[v] >= num[u])  joint[u] = 1;
        }
        else low[u] = min(low[u], num[v]);
    }
    tail[u] = dfsTime;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)    {
        int u,v;    cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!num[i])    dfs(i,-1);
    }
    int numJoint = 0;
    for (int i = 1; i <= n; i++)    numJoint += joint[i];
    
    /*
    cout << numBridge << '\n';
    for (auto [a,b] : bridges)         cout << a << " " << b << '\n';
    */
   
    /*
    cout << numJoint << '\n';
    for (int i = 1; i <= n; i++)        if (joint[i])       cout << i << " ";
    */
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
