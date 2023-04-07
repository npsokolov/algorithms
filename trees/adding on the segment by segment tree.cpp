#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct tp
{
    ll mn;
    ll add;
};

vector<tp> tree;
vector<ll> vec;
ll n;


void Push(ll v){
    if (2*v+1<4*n){
    tree[2*v].add+=tree[v].add;
    tree[2*v+1].add+=tree[v].add;
    tree[2*v].mn+=tree[v].add;
    tree[2*v+1].mn+=tree[v].add;
    tree[v].add=0;
    }
}

void build(ll tl, ll tr, ll v){
    if (tl==tr) {
        tree[v].mn = vec[tl];
        tree[v].add=0;
    }else{
        ll tm=(tl+tr)/2;
        build(tl,tm,2*v);
        build(tm+1,tr,2*v+1);
        tree[v].mn = min(tree[2*v].mn,tree[2*v+1].mn);
        tree[v].add=0;
    }
}

void add(ll tl, ll tr, ll v, ll l, ll r, ll m)
{
    if (l>tr || r<tl)
    {
        return;
    }
    Push(v);
    if (l<=tl && tr<=r){
        tree[v].add+=m;
        tree[v].mn+=m;
        return;
    }
    ll tm=(tl+tr)>>1;
    add(tl,tm,2*v,l,r,m);
    add(tm+1,tr,2*v+1,l,r,m);
    tree[v].mn=min(tree[v*2].mn,tree[2*v+1].mn);
}

ll min(ll tl, ll tr, ll v, ll l, ll r){
    if (l>tr || r<tl)
    {
        return INT64_MAX;
    }
    Push(v);
    if (l<=tl && tr<=r){
        return tree[v].mn;
    }
    ll tm=(tl+tr)>>1;
    ll m1 = min(tm+1,tr,2*v+1,l,r);
    ll m2 = min(tl,tm,2*v,l,r);
    return min(m1,m2);
    

}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    ll m,t,r,l,su=0,x;
    cin >> n;
    vec.resize(n);
    tree.resize(4*n+5);
    for (ll i = 0; i < n; ++i) {
        cin >> vec[i];
    }
    cin >> m;
    build(0,n-1,1);
    for (size_t i = 0; i < m; i++)
    {
        cin >> l >> r;
        if (cin.get()!=10){
            cin >> t;
            if (l<=r){
                add(0,n-1,1,l,r,t);
            }else{
                add(0,n-1,1,0,r,t);
                add(0,n-1,1,l,n-1,t);
            }
        }else{
            if (l<=r){
                cout << min(0,n-1,1,l,r) << endl;
            }else{
                cout << min(min(0,n-1,1,0,r),min(0,n-1,1,l,n-1)) << endl;
            }

        }
        
    }
    
    //add(v,tree,0,n-1,1,0,9,-1);
    //add(v,tree,0,n-1,1,3,3,3);
    //cout << sum(v,tree,0,n-1,1,0,9) << endl;


    return 0;
}
