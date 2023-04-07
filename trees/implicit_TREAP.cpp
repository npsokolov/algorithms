#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct TTreapNode
{
    int Count;
    int Priority;
    int Value;
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

private:
    std::shared_ptr<TTreapStorage> Storage_;

    int Index_;

    int MergeImpl(int left, int right);
    std::pair<int, int> SplitImpl(int current, int position);
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
    if (nodes[left].Priority < nodes[right].Priority) {
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
        Nodes[index].Count = 1 + GetCount(Nodes[index].Left) + GetCount(Nodes[index].Right);
    }
}


int main(){
    int n,m,l,r;
    cin >> n >> m;
    TTreap tree;
    for (int i = 0; i < n; ++i) {
        tree.Append(i);
    }
    while (m--){
        cin >> l >> r;
        l--; r--;
        auto x = tree.Cut(l,r);
        x.Append(tree);
        tree=move(x);
    }
    for (int i = 0; i < n; ++i) {
        cout << tree.Get(i)+1 << " ";
    }
    cout << endl;
}