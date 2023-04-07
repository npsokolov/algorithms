#include <bits/stdc++.h>

using namespace std;
#define ll long long

vector<vector<ll>> tree;
vector<ll> vec;
void build(ll tl, ll tr, ll v)
{
    if (tl==tr)
    {
        tree[v]={vec[tl]};
    }else{
        ll mid=(tl+tr)>>1;
        build(tl,mid,2*v);
        build(mid+1,tr,2*v+1);
        tree[v].resize(tree[2*v].size()+tree[2*v+1].size());
        merge(tree[2*v].begin(),tree[2*v].end(),tree[2*v+1].begin(),tree[2*v+1].end(),tree[v].begin());
    }
}

ll query(ll tl, ll tr, ll v, ll l, ll r, ll x)
{
    if (tl==l && tr==r)
    {
        return upper_bound(tree[v].begin(),tree[v].end(),x)-tree[v].begin();
    }
    ll mid = (tl+tr)>>1;
    if (r<=mid){
        return query(tl,mid,2*v,l,r,x);
    }else if (l>mid){
        return query(mid+1,tr,2*v+1,l,r,x);
    }else{
        return query(tl,mid,2*v,l,mid,x)+query(mid+1,tr,2*v+1,mid+1,r,x);
    };
}


int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ll n,m,u,v;
    cin >> n >> m;
    vec.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }
    tree.resize(4*n);
    build(0,n-1,1);
    while(m--){
        ll l,r,x;
        cin >> l >> r >> x;
        cout << query(0,n-1,1,l,r,x) << endl;
    }


    return 0;
}