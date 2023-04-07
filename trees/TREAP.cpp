#include <optional>
#include <vector>
#include <random>
#include <iostream>
using namespace std;

int GeneratePriority();

struct TreapNode
{
    int key,prior,left,right;
    TreapNode(int key_) : key(key_), left(-1), right(-1), prior(GeneratePriority()) {}
};

class Treap
{
public:
    void Insert(int key);
    bool Find(int key);
    optional<int> FindLowerBound(int key);
private:
    int Root=-1;
    vector<TreapNode> Nodes_;
    pair<int,int> Split(int cur, int key);
    int Merge(int left,int right);
};

int GeneratePriority()
{
    static mt19937 Generator(42);
    return uniform_int_distribution<int>()(Generator);
}

pair<int,int> Treap::Split(int cur, int key) {
    if (cur==-1){
        return {-1,-1};
    }
    if (Nodes_[cur].key>key){
        auto [l,r] = Split(Nodes_[cur].left,key);
        Nodes_[cur].left=r;
        return {l,cur};
    }else{
        auto [l,r] = Split(Nodes_[cur].right,key);
        Nodes_[cur].right=l;
        return {cur,r};
    }
}

int Treap::Merge(int left, int right) {
    if (left==-1){
        return right;
    }
    if (right==-1){
        return left;
    }
    if (Nodes_[left].prior<Nodes_[right].prior){
        Nodes_[right].left=Merge(left,Nodes_[right].left);
        return right;
    }else{
        Nodes_[left].right=Merge(Nodes_[left].right,right);
        return left;
    }
}

void Treap::Insert(int key) {
    auto [lm,r] = Split(Root,key);
    auto [l,m] = Split(lm,key-1);
    if (m==-1) {
        Nodes_.emplace_back(TreapNode(key));
        Root = Merge(l, Merge(Nodes_.size() - 1, r));
    }else{
        Root = Merge(l,Merge(m,r));
    }
}


bool Treap::Find(int key){
    bool flag=true;
    auto [lm,r] = Split(Root,key);
    auto [l,mid] = Split(lm,key-1);
    auto result = mid != -1;
    Root = Merge(l, Merge(mid, r));
    return result;

}

optional<int> Treap::FindLowerBound(int key) {
    int cur = Root;
    int res = -1;
    while (cur>=0){
        if (Nodes_[cur].key==key){
            res=cur;
            break;
        }else if (Nodes_[cur].key>key){
            res=cur;
            cur=Nodes_[cur].left;
        }else{
            cur=Nodes_[cur].right;
        }
    }
    return res ==-1 ? nullopt : optional<int>(Nodes_[res].key);
}

const int mod = 1e9;


int main(){
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,x,lastx;
    char c;
    Treap tree;
    cin >> n;
    char last='+';
    while (n--){
        cin >> c >> x;
        if (c=='+'){
            if (last=='?') {
                tree.Insert((x+lastx)%mod);
            }else{
                tree.Insert(x);
            }
        }else{
            auto f = tree.FindLowerBound(x);
            if (f){
                lastx=f.value();
                cout << f.value() << endl;
            }else{
                cout << -1 << endl;
                lastx=-1;
            }
        }
        last=c;
    }
    cout.flush();
    return 0;
}