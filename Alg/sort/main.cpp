#include <iostream>
#include <vector>
using namespace std;

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




int main()
{
    std::vector<int> mem = {4,5,1,2,9,10,23,11,66};
    //insertionSort(mem);
    mergeSort(mem,0,mem.size()-1);
    //merge(mem,0,2,3);

    for(auto p: mem)
        std::cout << p << ";" ;
    std::cout << endl;
    return 0;
}
