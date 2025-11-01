#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ll long long

const int N = 1e6 + 5;

ll n;
ll w[N];

ll t[N];
ll a[N], b[N];

ll p[N];
ll cnt[N];
ll mmin[N];
ll sum[N];

int find(int u) {
    if (u == p[u]) return u;
    return p[u] = find(p[u]);
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    for (int i = 1; i <= n; i++) {
        p[i] = i;
        cnt[i] = 1;
        mmin[i] = w[i];
        sum[i] = w[i];
    }

    for (int i = 1; i <= n; i++) {
        int u = a[i], v = b[i];

        u = find(u);
        v = find(v);

        if (u != v) {
            p[v] = u;
            cnt[u] += cnt[v];
            sum[u] += sum[v];
            mmin[u] = min(mmin[u], mmin[v]);
        }
    }

//    for (int i = 1; i <= n; i++) {
//        cout << find(i) << " ";
//    }
//    cout << endl;

    ll minw = 100000;
    for (int i = 1; i <= n; i++)  minw = min(minw, mmin[i]);
    ll res = 0;
    vector<int> reserve;

    for (int i = 1; i <= n; i++) {
        if (p[i] == i) {
            if (cnt[i] > 1) {
                ll t1 = sum[i] + mmin[i] * (cnt[i] - 2);
                ll t2 = sum[i] + 2 * minw + (cnt[i] - 2) * minw + minw + mmin[i];
                res += min(t1,t2);
            }
        }
    }
    cout << res << endl;
}

signed main() {
    cin.tie(0) -> sync_with_stdio();
    if (fopen("main.inp", "r")) freopen("main.inp", "r", stdin);

    int t = 1;
//    cin >> t;
    while (t--) solve();
}
