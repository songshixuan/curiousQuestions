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

	friend bool operator<=(const RetVal& l, const RetVal& r)
    {
        return l.max <= r.max;
    }
    friend bool operator>=(const RetVal& l,const RetVal& r){
        return !(l<=r);
    }
	friend bool operator==(const RetVal& l, const RetVal& r)
    {
        return l.max == r.max;
    }

};




std::ostream& operator<<(std::ostream& out, const RetVal& retVal)
{
       return out << retVal.i << " ; " << retVal.j << " ; " << retVal.max << "." << endl;

}
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

RetVal findMaxSubArr(const vector<int>& nums, int low, int high){
    if(low == high){
        return RetVal(low,low,nums[low]);
    }
    int mid = (low + high)/2;
    auto lRet = findMaxSubArr(nums,low,mid);
    auto rRet = findMaxSubArr(nums,mid+1,high);
    auto mRet = maxCrossing(nums,low,mid,high);
    if( lRet >= rRet && lRet >= mRet ){
        return lRet;
    }else if(rRet >= mRet && rRet >= lRet){
        return rRet;
    }else{
        return mRet;
    }

}



int main(){
    std::vector<int> nums {-2,1,-3,4,-1,2,1,-5,4};
    //auto r = maxCrossing(nums,0,(0+nums.size()-1)/2,nums.size()-1);
    //cout << r;
    auto ret = findMaxSubArr(nums,0,nums.size()-1);
    cout << ret;
    return 0;
}
