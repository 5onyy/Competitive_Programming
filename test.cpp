#include<bits/stdc++.h>

using namespace std;

pair <int, int> ans[1000005];
const int N = 2005;

int main()
{
    int t;
    cin >> t;
	int cnt = 0;
    vector <vector<long long>> a(N, vector <long long> (N,0));
    vector <vector<long long>> pref(N, vector <long long> (N,0));
	bool isEnd = false; 
    for (int i = 1; i < N; i++)
    {
        int j = 1;
        int ii = i;
        while (ii >= 1)
        {
			if (isEnd)		break;
            if (cnt > 1000000)
            {
				isEnd = true;
                break;
            }
            a[ii][j] = cnt * cnt;
            ans[cnt] = {ii, j};
            cnt++;
            j++;
            ii--;
        }
    }
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + a[i][j];
        }
    }
    while (t--)
    {
        int n;
        cin >> n;
        int x = ans[n].first;
        int y = ans[n].second;
        cout << pref[x][y] << '\n';
    }
}
