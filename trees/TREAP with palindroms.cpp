#include <bits/stdc++.h>

using namespace std;
#define ll long long
vector<int> p(3e5+100);
int mod = INT32_MAX;
struct TTreapNode
{
    int Count;
    int Priority;
    int Value;
    int Hash;
    int BackHash;
    int Left;
    int Right;
};

struct TTreapStorage
{
    std::vector<TTreapNode> Nodes;

    int AllocateNode(int value, int left, int right);
    int GetCount(int index) const;
    int GetPosition(int index) const;
    void InitCount(int index);
};

class TTreap
{
public:
    TTreap();
    TTreap(std::shared_ptr<TTreapStorage> storage, int index);

    TTreap Cut(int l, int r);

    void Append(int value);
    // #right can be changed and must not be used after the call.
    void Append(TTreap right);

    int Get(int position);

    std::shared_ptr<TTreapStorage> Storage_;

    int Index_;

    int MergeImpl(int left, int right);
    std::pair<int, int> SplitImpl(int current, int position);
    bool GetHash();
};



TTreap::TTreap()
        : Storage_(new TTreapStorage())
        , Index_(-1)
{ }

TTreap::TTreap(std::shared_ptr<TTreapStorage> storage, int index)
        : Storage_(std::move(storage))
        , Index_(index)
{ }

TTreap TTreap::Cut(int l, int r)
{
    assert(l <= r);
    assert(0 <= l);
    assert(r < Storage_->GetCount(Index_));
    auto [left, middleRight] = SplitImpl(Index_, l - 1);
    auto [middle, right] = SplitImpl(middleRight, r - l);
    Index_ = MergeImpl(left, right);
    return TTreap(Storage_, middle);
}

void TTreap::Append(int value)
{
    int index = Storage_->AllocateNode(value, -1, -1);
    Index_ = MergeImpl(Index_, index);
}

void TTreap::Append(TTreap right)
{
    assert(Storage_.get() == right.Storage_.get());
    Index_ = MergeImpl(Index_, right.Index_);
}

int TTreap::Get(int position)
{
    assert(0 <= position);
    assert(position < Storage_->GetCount(Index_));
    auto [leftMiddle, right] = SplitImpl(Index_, position);
    auto [left, middle] = SplitImpl(leftMiddle, position - 1);
    auto result = Storage_->Nodes[middle].Value;
    Index_ = MergeImpl(left, MergeImpl(middle, right));
    return result;
}

int TTreap::MergeImpl(int left, int right)
{
    if (left == -1) {
        return right;
    }
    if (right == -1) {
        return left;
    }
    auto& nodes = Storage_->Nodes;
    if (nodes[left].Priority > nodes[right].Priority) {
        nodes[left].Right = MergeImpl(nodes[left].Right, right);
        Storage_->InitCount(left);
        return left;
    } else {
        nodes[right].Left = MergeImpl(left, nodes[right].Left);
        Storage_->InitCount(right);
        return right;
    }
}

std::pair<int, int> TTreap::SplitImpl(int current, int position)
{
    if (current == -1) {
        return std::make_pair(-1, -1);
    }
    auto& nodes = Storage_->Nodes;
    int currentPosition = Storage_->GetPosition(current);
    if (currentPosition <= position) {
        auto [left, right] = SplitImpl(nodes[current].Right, position - currentPosition - 1);
        nodes[current].Right = left;
        Storage_->InitCount(current);
        return std::make_pair(current, right);
    } else {
        auto [left, right] = SplitImpl(nodes[current].Left, position);
        nodes[current].Left = right;
        Storage_->InitCount(current);
        return std::make_pair(left, current);
    }
}

int TTreapStorage::AllocateNode(int value, int left, int right)
{
    static std::mt19937 Generator(42);
    auto priority = std::uniform_int_distribution<int>()(Generator);

    Nodes.emplace_back();
    Nodes.back().Priority = priority;
    Nodes.back().Value = value;
    Nodes.back().Hash = value;
    Nodes.back().BackHash = value;
    Nodes.back().Left = left;
    Nodes.back().Right = right;
    InitCount(Nodes.size() - 1);

    return Nodes.size() - 1;
}

int TTreapStorage::GetCount(int index) const
{
    return index == -1 ? 0 : Nodes[index].Count;
}

int TTreapStorage::GetPosition(int index) const
{
    assert(index >= 0);
    assert(index < Nodes.size());
    return GetCount(Nodes[index].Left);
}

void TTreapStorage::InitCount(int index)
{
    if (index != -1) {
        int left = GetCount(Nodes[index].Left);
        int right = GetCount(Nodes[index].Right);
        Nodes[index].Hash = p[left]*Nodes[index].Value%mod;
        Nodes[index].BackHash = p[right]*Nodes[index].Value%mod;
        if (left) {
            Nodes[index].Hash = (Nodes[index].Hash+ Nodes[Nodes[index].Left].Hash)%mod;
            Nodes[index].BackHash = (Nodes[index].BackHash+ Nodes[Nodes[index].Left].BackHash*p[right+1]%mod)%mod;
        }
        if (right) {
            Nodes[index].Hash = (Nodes[index].Hash+ Nodes[Nodes[index].Right].Hash*p[left+1]%mod)%mod;
            Nodes[index].BackHash = (Nodes[index].BackHash+ Nodes[Nodes[index].Right].BackHash)%mod;
        }
        Nodes[index].Count = 1 + left + right;
    }
}

bool TTreap::GetHash()
{
    return Storage_->Nodes[Index_].Hash==Storage_->Nodes[Index_].BackHash;
}


int main(){
    int k=31;
    p[0] = 1;
    for (int i = 1; i < 3e5+50; i++)
        p[i] = (p[i-1] * k) % mod;

    int n,m,t;
    cin >> n >> m;
    TTreap tree;
    string str;
    cin >> str;
    for (int i = 0; i < n; ++i) {
        tree.Append(str[i]);
    }
    while (m--){
        cin >> t;
        if (t==1) {
            int l,r;
            cin >> l >> r;
            l--; r--;
            auto x = tree.Cut(l, r);
            n-=(r-l+1);
        }else if (t==2){
            char l;
            int r;
            cin >> l >> r;
            r--;
            if (r==0){
                TTreap x=tree.Cut(0,n-1);
                tree.Append(l);
                tree.Append(x);
            }else if (r==n){
                tree.Append(l);
            }else{
                auto x = tree.Cut(0,r-1);
                x.Append(l);
                x.Append(tree);
                tree=move(x);
            }
            n++;
        }else{
            int l,r;
            cin >> l >> r;
            l--; r--;
            if (l==0){
                TTreap x=tree.Cut(0,r);
                if (x.GetHash()){
                    cout << "yes" << endl;
                }else{
                    cout << "no" << endl;
                }
                x.Append(tree);
                tree=move(x);
            }else{
                auto x = tree.Cut(0,l-1);
                auto ans = tree.Cut(0,r-l);
                if (ans.GetHash()){
                    cout << "yes" << endl;
                }else{
                    cout << "no" << endl;
                }
                x.Append(ans);
                x.Append(tree);
                tree=move(x);
            }
        }
    }
}
