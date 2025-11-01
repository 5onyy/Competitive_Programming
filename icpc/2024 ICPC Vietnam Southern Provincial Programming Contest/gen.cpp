#include <bits/stdc++.h>

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;

ll randint(ll l, ll r) {
    return uniform_int_distribution<ll> (l,r) (rng);
}

double randdouble(double l, double r) {
    return uniform_real_distribution<double> (l,r) (rng);
}

signed main(signed argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n = randint(1,20);
    int p = randint(1, 20);
    int m = randint(1, 10);
    cout << n << ' ' << p << ' ' << m << '\n';
    for (int i = 1; i <= p; i++) {
        cout << randint(0, n - 1) << ' ' << randint(0, n - 1) << ' ' << randint(1, 4) << '\n';
    }
    vector<char> p = {'A', 'R', 'Z'};
    for (int i = 0; i < m; i++) {
        cout << p[randint(0, 2)] < " "
    }
    
    // generate test cases with same format as given in problem

    return 0;
}