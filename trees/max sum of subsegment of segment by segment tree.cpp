#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct tre
{
    ll suf;
    ll pref;
    ll sum;
    ll seg;
};

void build(vector<tre> &tree, vector<ll> &vec, ll l, ll r, ll v)
{
    if (l == r)
    {
        tree[v].suf=max(0ll,vec[l]);
        tree[v].pref=max(0ll,vec[l]);
        tree[v].sum=vec[l];
        tree[v].seg=max(0ll,vec[l]);
        return;
    }
    ll mid = (l + r) >> 1;
    build(tree, vec, l, mid, 2 * v);
    build(tree, vec, mid + 1, r, 2 * v + 1);
    tree[v].seg=max(tree[v*2].seg,max(tree[v*2+1].seg,tree[v*2].suf+tree[2*v+1].pref));
    tree[v].pref=max(tree[2*v].pref,tree[2*v].sum+tree[2*v+1].pref);
    tree[v].sum=tree[v*2].sum+tree[v*2+1].sum;
    tree[v].suf=max(tree[2*v].suf+tree[2*v+1].sum,tree[2*v+1].suf);
}

void update(vector<tre> &tree, vector<ll> &vec, ll pos, ll value, ll l, ll r, ll v)
{
    if (l == r && l == pos)
    {
        tree[v].suf=max(0ll,value);
        tree[v].pref=max(0ll,value);
        tree[v].sum=value;
        tree[v].seg=max(0ll,value);
        return;
    }
    ll mid = (l + r) >> 1;
    if (pos <= mid)
    {
        update(tree, vec, pos, value, l, mid, 2 * v);
    }
    else
    {
        update(tree, vec, pos, value, mid + 1, r, 2 * v + 1);
    }
    tree[v].seg=max(tree[v*2].seg,max(tree[v*2+1].seg,tree[v*2].suf+tree[2*v+1].pref));
    tree[v].pref=max(tree[2*v].pref,tree[2*v].sum+tree[2*v+1].pref);
    tree[v].sum=tree[v*2].sum+tree[v*2+1].sum;
    tree[v].suf=max(tree[2*v].suf+tree[2*v+1].sum,tree[2*v+1].suf);
}


tre getseg(vector<tre> &tree, vector<ll> &vec, ll tl, ll tr, ll l, ll r, ll v)
{
    if (tl == l && tr == r)
    {
        return tree[v];
    }
    ll mid = (tl + tr) >> 1;
    if (r <= mid)
    {
        return getseg(tree, vec, tl, mid, l, r, 2 * v);
    }
    if (l > mid)
    {
        return getseg(tree, vec, mid + 1, tr, l, r, 2 * v + 1);
    }
    auto a = getseg(tree, vec, tl, mid, l, mid, 2 * v);
    auto b = getseg(tree, vec, mid + 1, tr, mid+1, r, 2 * v + 1);
    tre c;
    c.sum=a.sum+b.sum;
    c.seg=max(a.seg,max(b.seg,a.suf+b.pref));
    c.pref=max(a.pref,a.sum+b.pref);
    c.suf=max(a.suf+b.sum,b.suf);
    return c;
}


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll r, l, su = 0, n, m, t = 0;
    cin >> n >> m;
    vector<tre> tree(4 * n + 4);
    vector<ll> vec(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        cin >> vec[i];
    }
    build(tree, vec, 1, n, 1);
    ll a, s, d;
    cout << tree[1].seg << endl;;
    for (size_t i = 0; i < m; i++)
    {
        cin >> s >> d;
        update(tree, vec, s + 1, d, 1, n, 1);
        cout << tree[1].seg << endl;
    }

    return 0;
}