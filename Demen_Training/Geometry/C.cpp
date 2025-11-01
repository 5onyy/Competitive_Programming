#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long
#define F first
#define S second
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


template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {return os << "(" << p.x << "," << p.y << ")";}
    friend istream& operator>>(istream& is, P p) {return is >> p.x >> p.y;}
};

template<class P> 
bool onSegment(P s,P e,P p){
    return p.cross(s,e) == 0 && (s-p).dot(e-p) < 0;
}

template<class P>
bool segmentIntersect(P s1, P e1, P s2, P e2) {
    if (s1 == s2 || s1 == e2 || e1 == s2 || e1 == e2)   return true;    // Intersect is one of the end points
    int c1 = s1.cross(s2,e2), c2 = e1.cross(s2,e2), c3 = s2.cross(s1,e1), c4 = e2.cross(s1,e1);
    if (onSegment(s1,e1,s2) || onSegment(s1,e1,e2) || onSegment(s2,e2,s1) || onSegment(s2,e2,e1))  return true; // Infinity point
    if (sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0)     return true;
    return false;
}

void solve() {
    Point<int> A,B,C,D;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
    if (segmentIntersect(A,B,C,D) == 1)    cout << "YES\n";
    else cout << "NO\n";
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    // freopen("t.inp", "r", stdin);
    // freopen("t.out", "w", stdout);
    int test;   cin >> test;    
    while (test--)  solve();
    return 0;
}


