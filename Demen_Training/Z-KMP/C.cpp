#include<bits/stdc++.h>

using namespace std;

int z[100005];

int zFunc(string s) {
    int l = 0, r = 0;
    int n = s.size();
    for (int i = 1; i < n; i++) {
        z[i] = 0;
        if (i <= r)       z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])      z[i]++;
        if (r < i + z[i] - 1) {
            l = i;      
            r = i + z[i] - 1;
        }
        if (n % i == 0 && i + z[i] - 1 == n - 1)        {   /// i la vi tri m trong sol cu~
            return n / i;
        }
    }
    return 1;
}

void solve() {
    string s;
    while (cin >> s) {
        if (s == "*")       break;
        cout << zFunc(s) << "\n";
    }
}

int32_t main() {
    cin.tie(0) -> sync_with_stdio(0);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
