//
// Created by root on 10/4/17.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <vector>
#include <iostream>
#include <algorithm>
class heap {
public:
    heap(const std::vector<int>&vec):mArray(1){
        for (auto m:vec){
            mArray.push_back(m);
        }
        mHeapSize = mArray.size()-1;
    }

    inline void maxHeapIFY(int i){
        int left = 2 * i,right = 2*i +1, largest = i;
        if (left <= mHeapSize && mArray[left] > mArray[largest]){
            largest = left;
        }
        if (right <= mHeapSize && mArray[right] > mArray[largest]){
            largest = right;
        }
        if (largest != i){
            std::swap(mArray[i],mArray[largest]);
            maxHeapIFY(largest);
        }

    }



    inline void buildHeap(){
        for(int i = mHeapSize/2;i > 0;--i){
            maxHeapIFY(i);
        }
    }

    inline void heapSort(){
        buildHeap();
        showArray("after building");
        for(int i = mHeapSize;i > 1; --i){
            std::swap(mArray[1],mArray[mHeapSize]);
            mHeapSize--;
            maxHeapIFY(1);
        }
    }

    inline void showArray(char *msg= nullptr){
        if (msg != nullptr){
            std::cout << msg << std::endl;
        }

        for(auto m:mArray){
            std::cout << m << ";" ;
        }
        std::cout << std::endl;
    }

protected:
    std::vector<int> mArray;
    int mHeapSize;


    inline  int parent(int i){
        return i/2;
    }

};


#endif //HEAP_HEAP_H
