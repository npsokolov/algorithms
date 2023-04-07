#include <bits/stdc++.h>

using namespace std;

#define ll long long

void build(vector<pair<ll, ll>> &tree, vector<ll> &vec, ll l, ll r, ll v)
{
    if (l == r)
    {
        tree[v] = {vec[l], 1};
        return;
    }
    ll mid = (l + r) >> 1;
    build(tree, vec, l, mid, 2 * v);
    build(tree, vec, mid + 1, r, 2 * v + 1);
    if (tree[2 * v].first == tree[2 * v + 1].first)
    {
        tree[v] = {tree[2 * v].first, tree[2 * v].second + tree[2 * v + 1].second};
    }
    else if (tree[2 * v].first < tree[2 * v + 1].first)
    {
        tree[v] = tree[2 * v];
    }
    else
    {
        tree[v] = tree[2 * v + 1];
    }
}

void update(vector<pair<ll, ll>> &tree, vector<ll> &vec, ll pos, ll value, ll l, ll r, ll v)
{
    if (l == r && l == pos)
    {
        tree[v] = {value, 1};
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
    if (tree[2 * v].first == tree[2 * v + 1].first)
    {
        tree[v] = {tree[2 * v].first, tree[2 * v].second + tree[2 * v + 1].second};
    }
    else if (tree[2 * v].first < tree[2 * v + 1].first)
    {
        tree[v] = tree[2 * v];
    }
    else
    {
        tree[v] = tree[2 * v + 1];
    }
}

pair<ll, ll> getmin(vector<pair<ll, ll>> &tree, vector<ll> &vec, ll tl, ll tr, ll l, ll r, ll v)
{
    if (tl == l && tr == r)
    {
        return tree[v];
    }
    ll mid = (tl + tr) >> 1;
    if (r <= mid)
    {
        return getmin(tree, vec, tl, mid, l, r, 2 * v);
    }
    if (l > mid)
    {
        return getmin(tree, vec, mid + 1, tr, l, r, 2 * v + 1);
    }
    auto q1 = getmin(tree, vec, tl, mid, l, mid, 2 * v);
    auto q2= getmin(tree, vec, mid + 1, tr, mid + 1, r, 2 * v + 1);
    if (q1.first==q2.first)
    {
        return {q1.first,q1.second+q2.second};
    }else if (q1.first<q2.first)
    {
        return q1;
    }else{
        return q2;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll r, l, su = 0, n, m, t = 0;
    cin >> n >> m;
    vector<pair<ll, ll>> tree(4 * n + 4, {0, 0});
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
            cout << getmin(tree, vec, 1, n, s + 1, d, 1).first << " " << getmin(tree, vec, 1, n, s + 1, d, 1).second << endl;
        }
    }

    return 0;
}