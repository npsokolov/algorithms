#include <bits/stdc++.h>
 
#define ll long long
 
using namespace std;

int m=INT32_MAX;
 
int hash_substring (int l, int r, vector<int>& h,vector<int>& p, int n) {
    return (h[r+1] - h[l]) * p[n-l] % m;
}

int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n,n1,l,r,t,su=0,X,Y,ans=0;
    int k=31;
    string str,s;
    cin >> n1;
    vector<string> vec(n1);
    vector<int> v(n1);
    int h=0;
    for (size_t i = 0; i < n1; i++)
    {
        cin >> vec[i];
        v[i]=vec.size();
        n=max(n,v[i]);
    }
    unordered_set<int> st;
    vector<int> p(n+5);
    p[0] = 1;
 
    for (int i = 1; i < n+4; i++)
        p[i] = (p[i-1] * k) % m;
    vector<vector<int>> hashvec(n1, vector<int>(n+1));
    for (size_t j = 0; j < n1; j++)
    {
        string str = vec[j];
        for (int i = 0; i < v[j]; i++)
            hashvec[j][i+1] = (hashvec[j][i] + str[i] * p[i]) % m;
    }
    //hash_substring(l,r,hashvec[i],p,n)
    
    
    
    
   
    
    return 0;
}  