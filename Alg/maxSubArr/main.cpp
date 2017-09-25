#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
struct RetVal{
    int i;
    int j;
    int max;

    RetVal(int low,int high,int _max):i(low),j(high),max(_max){

    }

};

RetVal maxCrossing(const vector<int>& vec,int low, int mid, int high){
    //left
    int lmax = INT_MIN,lsum = 0,left = 0;
    for (int i = mid; i >= low; --i ){
        lsum += vec[i];
        if (lsum > lmax){
            lmax = lsum;
            left = i;
        }
    }
    int rmax = INT_MIN,rsum = 0,right = 0;
    for (int i= mid +1 ; i <= high; ++i ){
        rsum += vec[i];
        if (rsum > rmax){
            rmax = rsum;
            right = i;
        }
    }


    return RetVal(left,right,lmax+rmax);
}


int main(){
    std::vector<int> words1 {1,2,3,4,5};
    //auto r = maxCrossing(vec,0,1,2);
    //std::cout << r;
    return 0;
}
