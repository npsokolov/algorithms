/*#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define _CRT_SECURE_NO_WARNINGS*/
#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<array>
#include<unordered_set>
#include<unordered_map>
#include<cstring>
#include<string>
#include<memory>
#include<iomanip>
#include<cassert>
#include<cmath>
#include<random>
#include<algorithm>
#include<chrono>
#include <unistd.h>
#include <complex>

using namespace std;
#define endl '\n'
#define int long long
#define ld long double

struct TTreapNode {
    int Count;
    int Priority;
    int Value;
    int Rev;
    int Left;
    int Right;
};

struct TTreapStorage {
    std::vector<TTreapNode> Nodes;

    int AllocateNode(int value, int left, int right) {
        static std::mt19937 Generator(42);
        auto priority = std::uniform_int_distribution<int>()(Generator);

        Nodes.emplace_back();
        Nodes.back().Priority = priority;
        Nodes.back().Value = value;
        Nodes.back().Rev = false;
        Nodes.back().Left = left;
        Nodes.back().Right = right;
        InitCount(Nodes.size() - 1);

        return Nodes.size() - 1;
    }

    int GetCount(int index) const { return index == -1 ? 0 : Nodes[index].Count; }

    int GetPosition(int index) const {
        assert(index >= 0);
        assert(index < Nodes.size());
        return GetCount(Nodes[index].Left);
    }

    void InitCount(int index) {
        if (index != -1) Nodes[index].Count = 1 + GetCount(Nodes[index].Left) + GetCount(Nodes[index].Right);
    }
};

class TTreap {
public:
    TTreap() : Storage_(new TTreapStorage()), Index_(-1) {}

    TTreap(std::shared_ptr<TTreapStorage> storage, int index) : Storage_(std::move(storage)), Index_(index) {}

    void Cut(int l, int r) {
        assert(l <= r);
        assert(0 <= l);
        assert(r < Storage_->GetCount(Index_));
        auto &nodes = Storage_->Nodes;
        auto [left, middleRight] = SplitImpl(Index_, l - 1);
        auto [middle, right] = SplitImpl(middleRight, r - l);
        if (middle != -1) {
            nodes[middle].Rev ^= 1;
            char c = nodes[middle].Value;
            if (islower(c)) {
                nodes[middle].Value = toupper(c);
            } else {
                nodes[middle].Value = tolower(c);
            }
            swap(nodes[middle].Right, nodes[middle].Left);
        }
        Index_ = MergeImpl(left, MergeImpl(middle, right));
    }

    void Append(int value) {
        int index = Storage_->AllocateNode(value, -1, -1);
        Index_ = MergeImpl(Index_, index);
    }

    // #right can be changed and must not be used after the call.
    void Append(TTreap right) {
        assert(Storage_.get() == right.Storage_.get());
        Index_ = MergeImpl(Index_, right.Index_);
    }

    int Get(int position) {
        assert(0 <= position);
        assert(position < Storage_->GetCount(Index_));
        auto [leftMiddle, right] = SplitImpl(Index_, position);
        auto [left, middle] = SplitImpl(leftMiddle, position - 1);
        auto result = Storage_->Nodes[middle].Value;
        Index_ = MergeImpl(left, MergeImpl(middle, right));
        return result;
    }

private:
    std::shared_ptr<TTreapStorage> Storage_;

    int Index_;

    void Push(int v) {
        if (v == -1) return;
        auto &nodes = Storage_->Nodes;
        if (nodes[v].Rev) {
            if (nodes[v].Right != -1) {
                nodes[nodes[v].Right].Rev ^= 1;
                char c = nodes[nodes[v].Right].Value;
                if (islower(c)) {
                    nodes[nodes[v].Right].Value = toupper(c);
                } else {
                    nodes[nodes[v].Right].Value = tolower(c);
                }
                swap(nodes[nodes[v].Right].Right, nodes[nodes[v].Right].Left);
            }
            if (nodes[v].Left != -1) {
                char c = nodes[nodes[v].Left].Value;
                if (islower(c)) {
                    nodes[nodes[v].Left].Value = toupper(c);
                } else {
                    nodes[nodes[v].Left].Value = tolower(c);
                }
                nodes[nodes[v].Left].Rev ^= 1;
                swap(nodes[nodes[v].Left].Right, nodes[nodes[v].Left].Left);
            }
        }
        nodes[v].Rev = false;
    }

    int MergeImpl(int left, int right) {
        if (left == -1) return right;
        if (right == -1) return left;
        Push(right);
        Push(left);
        auto &nodes = Storage_->Nodes;
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

    std::pair<int, int> SplitImpl(int current, int position) {
        if (current == -1) return std::make_pair(-1, -1);
        Push(current);
        auto &nodes = Storage_->Nodes;
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
};


void solve(){
    TTreap t;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // ONLINE_JUDGE
    int q = 1;
    //cin >> q;
    while (q--)
        solve();
    return 0;
}
