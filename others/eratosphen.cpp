#include <bits/stdc++.h>

#define ll long long

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll r, l, su = 0, n, m, t = 0;
    cin >> t;
    vector<bool> prime(t,true);
    prime[0]=prime[1]=0;
    for (int i = 2; i < t; ++i) {
        if (prime[i])
        {
            if (i*i<=t)
            {
                for (int j = i*i; j < t; j+=i) {
                    prime[j]=false;
                }
            }

        }

    }
    return 0;
}