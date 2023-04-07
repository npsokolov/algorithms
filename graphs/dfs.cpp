#include <bits/stdc++.h>

using namespace std;
#define ll long long
vector<vector<int>> graph(2e5+100);
vector<bool> used(2e5+100,false);
vector<ll> tin(2e5+100),tout(2e5+100);
ll tim=0;


void dfs(int v)
{
    used[v]=true;
    tin[v]=tim++;
    for (auto& u : graph[v])
    {
        if (!used[u]){
            dfs(u);
        }
    }
    tout[v]=tim++;
}

int main()
{

}