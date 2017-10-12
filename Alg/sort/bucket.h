#include <iostream>
#include <vector>
#include <list>
using namespace std;

void bucketSort(vector<float>& nums,int k,int bsize){
    int n = nums.size();
    //create 10 buckets
    vector<list<float>> buckets(bsize+1);
    int bIndex = 0;
    float tmp = 0;
    for(int i = 0; i < nums.size(); ++i){
        tmp = nums[i] / k;
        bIndex = tmp * n;
        std::cout << bIndex << " = " << tmp << "*" << n << std::endl;
        list<float>& l = buckets[bIndex];
        if (nums[i] < *l.begin()){
            l.push_front(nums[i]);
        }else{
            auto itr = l.begin();
            for(;itr != l.end();++itr){
                if(*itr > nums[i]){
                    break;
                }
            }
            itr--;
            l.insert(itr,nums[i]);

        }
    }

    int i = 0;
    for(auto list:buckets){

        for(auto m:list){
            nums[i++] = m;
        }
    }


}


void bucketTest(){
    vector<float> nums = {25,22,33,44,55,66,78,77,88,99,86};
    bucketSort(nums,100,10);
    for(auto m:nums){
        cout << m << ";";
    }
}
