#include <bits/stdc++.h>
 
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> s(n+1),dp(n+2,1e6),pos(n+2),prev(n+2);
    for (size_t i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    dp[0]=-3333333;
    pos[0]=-1;
    int x=0;
    for (size_t i = 0; i < n; i++)
    {
        int j=upper_bound(dp.begin(),dp.end(),s[i])-dp.begin();
        if (dp[j-1]<s[i] && s[i]<dp[j])
        {
            dp[j]=s[i];
            pos[j]=i;
            prev[i]=pos[j-1];
            x=max(x,j);
        }
    }
    auto k = pos[x];
    while (k!=-1)
    {
        cout << s[k] << " ";
        k=prev[k];
    }
    cout << endl;
    cout << x << endl;
    
    
    
    
    
    
}