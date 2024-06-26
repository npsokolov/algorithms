
#include <bits/stdc++.h>

using namespace std;

class Binary_Heap
{
public:
    Binary_Heap() : Heap_size(0), vec({}) {}
    Binary_Heap(vector<int>& vec1) : vec(vec1), Heap_size(vec1.size())
    {
        for (int i = Heap_size/2; i >= 0; i--)
        {
            SiftDown(i);
        }
    }
    void SiftDown(int i)
    {
        while (2*i+1<Heap_size)
        {
            auto left = 2*i+1;
            auto right = 2*i+2;
            auto temp=left;
            if (right<Heap_size && vec[right] < vec[left]) {
                temp=right;
            }
            if (vec[i]<=vec[temp]){
                break;
            }
            swap(vec[temp], vec[i]);
            i=temp;
        }

    }
    void SiftUp(int i)
    {
        while (vec[i]<vec[(i-1)/2]){
            swap(vec[i],vec[(i-1)/2]);
            i=(i-1)/2;
        }
    }
    int GetMin(){
        return vec[0];
    }
    int ExtractMin(){
        auto it = vec[0];
        vec[0]=vec[Heap_size-1];
        vec.pop_back();
        Heap_size--;
        SiftDown(0);
        return it;
    }
    void insert(int value){
        Heap_size++;
        vec.push_back(value);
        SiftUp(Heap_size-1);
    }

private:
    size_t Heap_size;
    vector<int> vec;
};



int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m, l, x, t;
    string str, s;
    Binary_Heap heap = Binary_Heap();
    heap.insert(10);
    heap.insert(9);
    heap.insert(12);
    heap.insert(8);
    heap.insert(9);
    cout << heap.ExtractMin() << endl;
    cout << heap.ExtractMin() << endl;
    cout << heap.ExtractMin() << endl;
    cout << heap.ExtractMin() << endl;
    vector<int> vec = {1, 4, 7, 2, 1, 2, 0};
    Binary_Heap heap1(vec);
    cout << heap1.ExtractMin() << endl;
    cout << heap1.ExtractMin() << endl;
    cout << heap1.ExtractMin() << endl;
    cout << heap1.ExtractMin() << endl;


    return 0;
}
