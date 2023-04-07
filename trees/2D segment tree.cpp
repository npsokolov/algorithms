#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define f first
#define s second

void build_Y(vector<vector<int>>& vec, vector<vector<int>>& tree, int lx, int rx, int vx, int ly, int ry, int vy)
{
    if (ly==ry)
    {
        if (lx==rx)
        {
            tree[vx][vy]=vec[lx][ly];
        }else{
            tree[vx][vy]=min(tree[2*vx][vy],tree[2*vx+1][vy]);
        }
    }else{
        int midy=(ly+ry)>>1;
        build_Y(vec, tree, lx, rx, vx, ly,midy,2*vy);
        build_Y(vec, tree, lx, rx, vx, midy+1,ry,2*vy+1);
        tree[vx][vy]=min(tree[vx][2*vy],tree[vx][2*vy+1]);
    }
}

void build_X(vector<vector<int>>& vec, vector<vector<int>>& tree, int lx, int rx, int vx, int m)
{
    if (lx!=rx)
    {
        int midx = (lx+rx)>>1;
        build_X(vec, tree, lx, midx, 2*vx, m);
        build_X(vec, tree, midx+1, rx, 2*vx+1, m);
    }
    build_Y(vec,tree,lx,rx,vx,0,m-1,1);
}

void update_Y(vector<vector<int>>& vec, vector<vector<int>>& tree, int lx, int rx, int vx, int ly, int ry, int vy, int x, int y, int val)
{
    if (ly==ry)
    {
        if (lx==rx)
        {
            tree[vx][vy]=val;
        }else{
            tree[vx][vy]=min(tree[2*vx][vy],tree[2*vx+1][vy]);
        }
    }else{
        int midy=(ly+ry)>>1;
        if (y<=midy){
            update_Y(vec, tree, lx, rx, vx, ly,midy,2*vy, x, y, val);
        }else{
            update_Y(vec, tree, lx, rx, vx, midy+1,ry,2*vy+1, x, y, val);
        }
        tree[vx][vy]=min(tree[vx][2*vy],tree[vx][2*vy+1]);
    }
}

void update_X(vector<vector<int>>& vec, vector<vector<int>>& tree, int lx, int rx, int vx, int m, int x, int y, int val)
{
    if (lx!=rx)
    {
        int midx = (lx+rx)>>1;
        if (x<=midx){
            update_X(vec, tree, lx, midx, 2*vx, m, x, y, val);
        }else{
            update_X(vec, tree, midx+1, rx, 2*vx+1, m, x , y , val);
        }
    }
    update_Y(vec,tree,lx,rx,vx,0,m-1,1,x,y,val);
}

int get_Y(vector<vector<int>>& vec, vector<vector<int>>& tree, int vx, int ly, int ry, int vy, int qly, int qry)
{
    if (ly==qly && ry==qry)
    {
        return tree[vx][vy];
    }
    int midy=(ly+ry)>>1;
    if (qry<=midy)
    {
        return get_Y(vec,tree,vx,ly,midy,2*vy,qly,qry);
    }else if (qly>midy){
        return get_Y(vec,tree,vx,midy+1,ry,2*vy+1,qly,qly);
    }else{
        return min(get_Y(vec,tree,vx,ly,midy,2*vy,qly,midy),get_Y(vec,tree,vx,midy+1,ry,2*vy+1,midy+1,qry));
    }

}

int get_X(vector<vector<int>>& vec, vector<vector<int>>& tree, int lx, int rx, int vx, int m, int qlx, int qrx, int qly, int qry)
{
    if (lx==qlx && rx==qrx)
    {
        return get_Y(vec,tree,vx,0,m-1,1,qly,qry);
    }
    int midx=(lx+rx)>>1;
    if (qrx<=midx)
    {
        return get_X(vec,tree,lx,midx,2*vx,m,qlx,qrx,qly,qry);
    }else if (qlx>midx){
        return get_X(vec,tree,midx+1,rx,2*vx+1,m,qlx,qrx,qly,qry);
    }else{
        return min(get_X(vec,tree,lx,midx,2*vx,m,qlx,midx,qly, qry),get_X(vec,tree,midx+1,rx,2*vx+1,m,midx+1,qrx,qly, qry));
    }

}





int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m, t, k, q, l, r;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    vector<vector<int>> tree(4*n, vector<int>(4*m));
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            cin >> v[i][j];
        }
    }
    build_X(v,tree,0,n-1,1,m);
    //update_X(v,tree,0,n-1,1,m,3,3,-100);
    cout << get_X(v,tree,0,n-1,1,m,1,3,3,3) << endl;

    return 0;
}
/*
4 4
1 2 3 4
2 3 4 5
4 3 10 2
3 4 2 3


2
*/
