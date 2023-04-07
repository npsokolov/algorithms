#include <bits/stdc++.h>

using namespace std;
#define ll long long

vector<vector<vector<ll>>> tree;
ll n;

void modify(ll x, ll y, ll z, ll d){
    for (ll i = x; i < n; i=i|(i+1))
        for (ll j = y; j < n; j=j|(j+1))
            for (ll k = z; k < n; k=k|(k+1))
                tree[i][j][k]+=d;
}

ll sm(ll x, ll y, ll z){
    ll result = 0;
    for (ll i = x; i > 0; i=(i&(i+1))-1)
        for (ll j = y; j > 0; j=(j&(j+1))-1)
            for (ll k = z; k > 0; k=(k&(k+1))-1)
                result+=tree[i][j][k];
    return result;
}

ll sum(ll x1, ll y1, ll z1, ll x2,ll y2,ll z2){
    ll result = sm(x2,y2,z2);
    result-=sm(x1-1,y2,z2)+sm(x2,y1-1,z2)+sm(x2,y2,z1-1);
    result+=sm(x1-1,y1-1,z2)+sm(x1-1,y2,z1-1)+sm(x2,y1-1,z1-1);
    result-=sm(x1-1,y1-1,z1-1);
    return result;

}




int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    ll m,x1,x2,y1,y2,z1,z2,k;
    cin >> n;
    n++;
    cin >> m;
    vector<vector<vector<ll>>> tree1(n,vector<vector<ll>>(n,vector<ll>(n)));
    tree=tree1;
    while (m!=3){
        if (m==1){
            cin >> x1 >> y1 >> z1 >> k;
            modify(x1+1,y1+1,z1+1,k);
        }else{
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << sum(x1+1,y1+1,z1+1,x2+1,y2+1,z2+1) << endl;
        }
        cin >> m;
    }

    
    return 0;
}