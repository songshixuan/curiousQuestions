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

int main()
{
    std::vector<int> mem = {7,8,9,1,2,3};
    insertionSort(mem);
    for(auto p: mem)
        std::cout << p << ";" ;
    std::cout << endl;
    return 0;
}
