#include <bits/stdc++.h>

using namespace std;
int rmq(int l, int r, vector<vector<int>>& sparsetable)
{
    int lg = __lg(r-l);
    return min(sparsetable[lg][l],sparsetable[lg][r-(1<<lg)]);
}
int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,m,x,t;
    string str,s;
    cin >> n ;
    vector<int> vec(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    int lg = __lg(n);
    //cout << lg << endl;
    vector<vector<int>> sparsetable(lg+1,vector<int>(n));
    for (size_t i = 0; i < n; i++)
    {
        sparsetable[0][i]=vec[i];
    }
    
    for (size_t i = 1; i <= lg; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            sparsetable[i][j]=min(sparsetable[i-1][j],sparsetable[i-1][min(int(j+(1<<(i-1))),n-1)]);
        }
    }
    int l,r,q;
    cin >> q;
    while (q--)
    {
        cin >> l >> r;
        cout << rmq(l,r+1,sparsetable) << endl;
    }

    
    return 0;
}   