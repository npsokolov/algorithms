#include <bits/stdc++.h>

using namespace std;
#define ll long long
vector<vector<int>> graph(2e5+100);
vector<bool> used(2e5+100,false);
ll tim=0;
void bfs(int from){
    queue<int> q;
    q.emplace(from);
    int ans;
    while (!q.empty()){
        int v = q.front();
        q.pop();
        for (auto& x : graph[v]) {
            if (!used[x]){
                used[x]=true;
                q.emplace(x);
            }
        }
    }
}

int main()
{
    
}