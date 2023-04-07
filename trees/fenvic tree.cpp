#include <bits/stdc++.h>

using namespace std;
#define ll long long

vector<int> vec;
vector<int> tree;
int n;

void modify(int i, int d){
    while (i<n){
        tree[i]+=d;
        i|=(i+1);
    }
}

void Set(int i, int x){
    int d=x-vec[i];
    vec[i]=x;
    modify(i,d);
}

void build(){
    for (int i = 0; i < n; i++)
    {
        modify(i,vec[i]);
    }
    
}

int sm(int i){
    int result = 0;
    while (i>=0){
        result+=tree[i];
        i=(i&(i+1))-1;
    }
    return result;
}

int sum(int l, int r){
    if (l==0){
        return sm(r);
    }
    return sm(r)-sm(l-1);
}



int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int m,l,x,t;
    cin >> n;
    vec.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    tree.resize(n);
    build();
    auto& t1 = tree;
    auto& v = vec;
    Set(4,4);


    
    return 0;
}