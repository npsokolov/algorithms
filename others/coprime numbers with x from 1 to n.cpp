#include <bits/stdc++.h>

using namespace std;

void printPrimeFactors(int n, unordered_set<int> &st)
{
    while (n % 2 == 0)
    {
        st.insert(2);
        n = n / 2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        while (n % i == 0)
        {
            st.insert(i);
            n = n / i;
        }
    }
    if (n > 2)
        st.insert(n);
}
/*
void printPrimeFactors(int n, unordered_set<int> &st)
{
    for (int i = 2; i <= sqrt(n); i = i + 1)
    {
        while (n % i == 0)
        {
            st.insert(i);
            n = n / i;
        }
    }
    if (n > 2)
        st.insert(n);
}
*/

int main()
{
    int n,x,ans;
    cin >> n;
    cin >> x;
    unordered_set<int> st;
    printPrimeFactors(x, st);
    vector<int> vec;
    for (auto x : st)
    {
    //    cout << x << " ";
        vec.push_back(x);
    }
    cout << endl;
    auto s = vec.size();
    ans=n;
    for (auto i =1; i< (1<<s);i++)
    {
        int count=0,q=1;

        for (size_t j = 0; j < s; j++)
        {
            if ((i>>j)&1)
            {
                count++;
                q*=vec[j];
            }
        }
        ans+=int(pow(-1,count))*(n/q);
        
    }
    cout << ans << endl;
    return 0;
}