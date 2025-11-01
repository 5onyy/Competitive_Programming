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

int pow10[11];

int encode(const vi &nums) { // {1,2,3,4} ---> 4321
    int ans = 0;
    for (int i = 0; i < 9; i++)  ans += nums[i] * pow10[i];
    return ans;
}

vi decode(int num) { // 98765 --> {5,6,7,8,9}
    vi ans;
    while (num) {
        ans.pb(num % 10);
        num /= 10;
    }
    return ans;
}


void solve() {
    pow10[0] = 1;
    for (int i = 1; i <= 10; i++)   pow10[i] = pow10[i - 1] * 10;
    vi start;
    for (int i = 1; i <= 3; i++)    for (int j = 1; j <= 3; j++) {
        int x;  cin >> x;
        start.pb(x);
    }
    unordered_map<int, int> vis;
    int s = encode(start);
    queue<ll> q;
    vis[s] = 1;
    q.push(s);
    while (sz(q)) {
        int u = q.front();  q.pop();
        vi nums = decode(u);
        // next_state
        for (int i = 0; i < 3; i++)    {   // right_shift
            for (int j = 0; j < 2; j++) {
                int old_idx = i * 3 + j;
                int new_idx = i * 3 + j + 1;
                swap(nums[old_idx],nums[new_idx]);
                int v = encode(nums);
                if (vis[v] == 0)    q.push(v),  vis[v] = vis[u] + 1;
                swap(nums[old_idx],nums[new_idx]);
            }
        }
        
        // next_state
        for (int i = 0; i < 2; i++)    {   // down_shift
            for (int j = 0; j < 3; j++) {
                int old_idx = i * 3 + j;
                int new_idx = (i+1) * 3 + j;
                swap(nums[old_idx],nums[new_idx]);
                int v = encode(nums);
                if (vis[v] == 0)    q.push(v),  vis[v] = vis[u] + 1;
                swap(nums[old_idx],nums[new_idx]);
            }
        }
    }
    vi end_state = {1,2,3,4,5,6,7,8,9};
    int stop = encode(end_state);
    cout << vis[stop] - 1;
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    solve();
    return 0;
}
