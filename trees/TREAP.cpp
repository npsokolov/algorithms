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
    int Priority;
    int Value;
    int Num;
    long long Sum;
    int Left;
    int Right;
};

struct TTreapStorage {
    std::vector<TTreapNode> Nodes;

    int AllocateNode(int value, int num, int left, int right){
        static std::mt19937 Generator(42);
        auto priority = std::uniform_int_distribution<int>()(Generator);

        Nodes.emplace_back();
        Nodes.back().Priority = priority;
        Nodes.back().Value = value;
        Nodes.back().Num = num;
        Nodes.back().Sum = num;
        Nodes.back().Left = left;
        Nodes.back().Right = right;
        InitCount(Nodes.size() - 1);

        return Nodes.size() - 1;
    }

    void InitCount(int index){
        if (index != -1) {
            Nodes[index].Sum = Nodes[index].Num;
            if (Nodes[index].Left != -1) {
                Nodes[index].Sum += Nodes[Nodes[index].Left].Sum;
            }
            if (Nodes[index].Right != -1) {
                Nodes[index].Sum += Nodes[Nodes[index].Right].Sum;
            }
        }
    }
};

class TTreap {
public:
    TTreap() : Storage_(new TTreapStorage()), Index_(-1) {}

    TTreap(std::shared_ptr<TTreapStorage> storage, int index) : Storage_(std::move(storage)), Index_(index) {}

    std::shared_ptr<TTreapStorage> Storage_;

    int Index_;

    // #right can be changed and must not be used after the call.
    void Append(TTreap right){
        assert(Storage_.get() == right.Storage_.get());
        Index_ = Merge(Index_, right.Index_);
    }

    int Merge(int left, int right){
        if (left == -1)return right;
        if (right == -1)return left;
        auto &nodes = Storage_->Nodes;
        if (nodes[left].Priority > nodes[right].Priority) {
            nodes[left].Right = Merge(nodes[left].Right, right);
            Storage_->InitCount(left);
            return left;
        } else {
            nodes[right].Left = Merge(left, nodes[right].Left);
            Storage_->InitCount(right);
            return right;
        }
    }

    std::pair<int, int> Split(int current, int key){
        if (current == -1) return std::make_pair(-1, -1);
        auto &nodes = Storage_->Nodes;
        if (nodes[current].Value <= key) {
            auto [left, right] = Split(nodes[current].Right, key);
            nodes[current].Right = left;
            Storage_->InitCount(current);
            return std::make_pair(current, right);
        } else {
            auto [left, right] = Split(nodes[current].Left, key);
            nodes[current].Left = right;
            Storage_->InitCount(current);
            return std::make_pair(left, current);
        }
    }

    void Insert(int key,int num){
        auto [left, right] = Split(Index_, key - 1);
        auto &nodes = Storage_->Nodes;
        int index = Storage_->AllocateNode(key, num, -1, -1);
        left = Merge(left, index);
        Index_ = Merge(left, right);
    }
};




void solve() {
    int n, m;
    cin >> n;

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
