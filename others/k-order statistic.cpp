#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll part(vector<ll>& vec, ll l, ll r)
{
    ll i=l;
    ll j = r;
    ll pivot = vec[(l+r)/2];
    while (i<=j)
    {
        while (vec[i]<pivot)
        {
            i++;
        }
        while (vec[j]>pivot)
        {
            j--;
        }
        if (i>=j)
        {
            break;

        }
        swap(vec[i++],vec[j--]);
    }
    return j;
}

ll k(vector<ll> vec, ll k)
{
    ll l = 0;
    ll r = vec.size()-1;
    while (1)
    {
        int m = part(vec,l,r);
        if (m>k)
        {
            r=m;

        }else if (m<k)
        {
            l=m+1;
        }else{
            return vec[m];
        }
    }
}

int main()
{
    vector<ll> vec = {1,5,3,2,4,2,3};
    cout << k(vec, 5) << endl;
}