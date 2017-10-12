#include <iostream>
#include <vector>
using namespace std;

//elements start from 0 to k [0,k]
vector<int> countingSort(vector<int> & nums,int k){
    int l = nums.size();
    vector<int> cArr(k+1);
    vector<int> bArr(l);
    //counting
    for(auto m:nums){
        cArr[m]++;
    }
    //counting nums no more than
    for(int i = 1; i <= k; ++i){
        cArr[i] = cArr[i-1] + cArr[i];
    }
    //so far we know the postion of A[i]
    for(int i = 0;i < l; ++i){
        bArr[cArr[nums[i]]-1] = nums[i];
    }

    return bArr;

}

void countingSortTestCase(){
    vector<int> arr = {6,9,23,25,1,0,2};
    int k = 25;
    auto res = countingSort(arr,k);
    for(auto m :res){
        cout << m << ";";
    }
}






