#include <bits/stdc++.h>

using namespace std;
using ll = long long;
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
ll Rand(ll l, ll h)
{
     assert(l <= h);
     ll res = 0;
     for (int i = 0; i < 4; i++)
           res = (res << 15) ^ (rd() & ((1 << 15) - 1));
     return l + res % (h - l + 1);
}


signed main(signed argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // generate test cases with same format as given in problem
    int n = Rand(1,100);
    cout << n << ' ' << Rand(1,n) << endl;
    
    for (int i = 1; i <= n; i++)    {
        for (int j = 1; j <= 10; j++)   cout << Rand(1,9);
        cout << endl;
    }
    return 0;
}