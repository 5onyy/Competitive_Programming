#include <bits/stdc++.h>

using namespace std;

using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const string NAME = "";
const int NTEST = 5;

ll randint(ll l, ll r) {
    return uniform_int_distribution<ll> (l,r) (rng);
}

ll randdouble(double l, double r) {
    return uniform_real_distribution<double> (l,r) (rng);
}

signed main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++) {
      ofstream inp((NAME + ".inp").c_str());
      // gen code ( inp << . . . << . . . )
      inp.close();

      system(("./" + NAME + ".exe").c_str());      // ( NAME)
      system(("./" + NAME + "_ans.exe").c_str()); // (NAME + ”_ans” )

      if (system(("fc " + NAME + ".out " + NAME + ".ans").c_str()))
      { // fc : Windows <−> diff : Linux
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
      }
      cout << "Test " << iTest << ": CORRECT!\n";
    }
      return 0;
}
