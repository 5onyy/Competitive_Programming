#include<bits/stdc++.h>
using namespace std;
int c[1000001],n;
void solve()
{
    memset(c,0,sizeof c);
    for (int i=2;i<=1000000;i++)
    {
        if (c[i]==0)
            for (int j=i;j<=1000000;j+=i)
                c[j]++;
    }

}
int main()
{
    freopen("10699.INP","r",stdin);
    freopen("10699.OUT","w",stdout);
    solve();
    while (scanf("%d", &n), n)
    {
        if (n!=0)
        {
            printf("%d : %d\n", n, c[n]);
        }
    }
    return 0;
}
