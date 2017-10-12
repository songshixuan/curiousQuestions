#include <iostream>
#include <vector>
using namespace std;
#include "counting_sort.h"
void insertionSort(vector<int> &nums){
    int len = nums.size();
    if (len < 2){
        return;
    }
    int j = 0;
    int tmp = 0;
    for(int i = 1; i < len; ++i ){
         j = i;
        tmp = nums[i];
         while(j > 0 && tmp < nums[j-1] ){
             nums[j] = nums[j-1];
             --j;
         }
         nums[j] = tmp;
    }
}

/*
 * merge sort; divide and conquer;Recursive
 *
 * merge: merge to ordered array into one ordered array
 *
 */

void merge(vector<int>&nums,int p,int q,int r){
    int i = p, j = q;
    vector<int> tmp;
    while (i <= q-1 && j <= r){
        if(nums[i] < nums[j]){
            tmp.push_back(nums[i]);
            i++;
        }else{
            tmp.push_back(nums[j]);
            j++;
        }
    }
    //copy rest
    while (i <= q-1){
        tmp.push_back(nums[i++]);
    }
    while (j <= r){
        tmp.push_back(nums[j++]);
    }


    //copy back
    int l = tmp.size();
    for(int index = 0;index < l;++index){
        nums[p++] = tmp[index];
    }

}

void mergeSort(vector<int>&nums,int p, int r){
    if(r > p){
        int q = (r+p)/2;
        mergeSort(nums,p,q);
        mergeSort(nums,q+1,r);

        merge(nums,p,q+1,r);
    }
}



/*
 *  used by quickSort
 * return pivot
 */
int partition(vector<int>& nums,int p,int r){
    //get the pivot
    int x = nums[r];
    int i = p - 1;
    for (int j = p; j < r ; ++j){
        if(nums[j] <= x){
            ++i;
            std::swap(nums[j],nums[i]);
        }
    }
    std::swap(nums[i+1],nums[r]);
    return i+1;
}


/*
 *
 */
void quickSort(vector<int>& nums,int p,int r){

    if(p < r){
        //divide
        auto pivot = partition(nums,p,r);
        quickSort(nums,p,pivot-1);
        quickSort(nums,pivot+1,r);
        //no need to merge
    }

}

int main()
{
    /*
    std::vector<int> mem = {4,5,1,2,9,10,23,11,66};
    quickSort(mem,0,mem.size()-1);
    for(auto p: mem)
        std::cout << p << ";" ;
    std::cout << endl;
    */
    countingSortTestCase();
    return 0;
}
