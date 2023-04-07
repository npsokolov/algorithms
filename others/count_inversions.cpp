#include <bits/stdc++.h>

using namespace std;

int h = 0;

void mergesort(vector<int> &vec, int l1,int mid, int r1, int& ans)
{
    int l=0;
    int r=0;
    vector<int> v(r1-l1);
    while (l1+l<mid and mid+r<r1)
    {
        if (vec[l1+l]<=vec[mid+r]){
            v[l+r]=vec[l1+l];
            l++;
        }else{
            v[l+r]=vec[mid+r];
            r++;
            ans+=mid-l1-l;
        }
    }
    while (l1+l<mid){
        v[l+r]=vec[l1+l];
        l++;
    }
    while (mid+r<r1){
        v[l+r]=vec[mid+r];
        r++;
    }
    for (size_t i = 0; i < l+r; i++)
    {
        vec[l1+i]=v[i];
    }
}
 
void mergesort1(vector<int> &vec, int l1, int r1, int& ans)
{
    if (l1+1>=r1){
        return;
    }
    int mid = (l1+r1)/2;
    mergesort1(vec,mid,r1,ans);
    mergesort1(vec,l1,mid,ans);
    mergesort(vec,l1,mid,r1,ans);
}

int count_inversions(vector<int>& vec)
{
    int ans=0;
    mergesort1(vec,0,vec.size(),ans);
    return ans;
}

int main()
{
    vector<int> vec={5,8,4,3,5};
    cout << count_inversions(vec) << endl;
}