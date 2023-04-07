#include <bits/stdc++.h>

using namespace std;

#define ll long long

void build(vector<ll> &tree, vector<ll> &vec, ll l, ll r, ll v)
{
    if (l == r)
    {
        tree[v] = vec[l];
        return;
    }
    ll mid = (l + r) >> 1;
    build(tree, vec, l, mid, 2 * v);
    build(tree, vec, mid + 1, r, 2 * v + 1);
    tree[v] =  tree[2 * v] + tree[2 * v + 1];
}

void update(vector<ll> &tree, vector<ll> &vec, long long pos, long long value, long long l, long long r, long long v)
{
    if (l == r && l == pos)
    {
        tree[v] = value;
        return;
    }
    ll mid = (l + r) / 2;
    if (mid >= pos)
    {
        update(tree, vec, pos, value, l, mid, 2 * v);
    }
    else
    {
        update(tree, vec, pos, value, mid + 1, r, 2 * v + 1);
    }

    tree[v] = tree[2 * v + 1] + tree[2 * v];
}

ll getsum(vector<ll> &tree, vector<ll> &vec, ll tl, ll tr, long long l, long long r, long long v)
{
    if (tl == l && tr == r)
    {
        return tree[v];
    }
    ll mid = (tl + tr) >> 1;
    if (r <= mid)
    {
        return getsum(tree, vec, tl, mid, l, r, 2 * v);
    }
    if (l > mid)
    {
        return getsum(tree, vec, mid + 1, tr, l, r, 2 * v + 1);
    }
    return getsum(tree, vec, tl, mid, l, mid, 2 * v)+ getsum(tree, vec, mid + 1, tr, mid + 1, r, 2 * v + 1);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll r, l, su = 0, n, m, t = 0;
    cin >> n >> m;
    vector<ll> tree(4 * n + 4);
    vector<ll> vec(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        cin >> vec[i];
    }
    build(tree, vec, 1, n, 1);
    ll a, s, d;
    for (size_t i = 0; i < m; i++)
    {
        cin >> a >> s >> d;
        if (a == 1)
        {
            update(tree, vec, s + 1, d, 1, n, 1);
        }
        else
        {
            cout << getsum(tree, vec, 1, n, s+1, d, 1) << endl;
        }
    }

    return 0;
}