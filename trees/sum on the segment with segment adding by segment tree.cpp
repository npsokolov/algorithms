#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define f first
#define s second
ll n;
struct tp
{
    ll mn;
    ll add;
};

vector<tp> tree;
vector<ll> vec;

void Push(ll v, ll tl, ll tr){
    ll mid = (tl+tr)>>1;
    tree[2*v].add+=tree[v].add;
    tree[2*v+1].add+=tree[v].add;
    tree[2*v].mn+=tree[v].add*(mid-tl+1);
    tree[2*v+1].mn+=tree[v].add*(tr-mid);
    tree[v].add=0;
}

void add(ll tl, ll tr, ll v, ll l, ll r, ll m)
{
    auto& j = tree;
    if (l==tl && tr==r){
        tree[v].add+=m;
        tree[v].mn+=m*(tr-tl+1);
        return;
    }
    Push(v,tl,tr);
    ll tm=(tl+tr)>>1;
    if (r<=tm) {
        add(tl, tm, 2 * v, l, r, m);
    }else if (l>tm) {
        add(tm + 1, tr, 2 * v + 1, l, r, m);
    }else{
        add(tl, tm, 2 * v, l, tm, m);
        add(tm + 1, tr, 2 * v + 1, tm+1, r, m);
    }
    tree[v].mn=tree[v*2].mn+tree[2*v+1].mn;
}

ll min(ll tl, ll tr, ll v, ll pos){
    if (tl==tr){
        return tree[v].mn;
    }
    Push(v,tl,tr);
    ll tm=(tl+tr)>>1;
    if (pos<=tm) {
        return min(tl,tm,2*v,pos);
    }else{
        return min(tm + 1, tr, 2 * v + 1, pos);
    }


}

int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);


    return 0;
}