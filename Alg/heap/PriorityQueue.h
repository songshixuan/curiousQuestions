//
// Created by root on 10/7/17.
//

#ifndef HEAP_PRIORITYQUEUE_H
#define HEAP_PRIORITYQUEUE_H

#include <limits.h>
#include "heap.h"
class MaxPriorityQueue: public heap {
public:
    MaxPriorityQueue(const std::vector<int>&vec):heap(vec){
        buildHeap();
    }

    inline bool insertToMaxHeap(int val){
        mArray.push_back(INT_MIN);
        mHeapSize++;
        increaseKey(mHeapSize,val);

    }

    inline int max(){
        return mArray[1];
    }

    inline bool isEmpty(){
        return mHeapSize == 0;
    }

    inline int extractMax(){
        if (mHeapSize == 0){
            try {
                throw "empty heap";
            }
            catch (const char* e){
                std::cout << e << std::endl;
            }
        }


        auto max = mArray[1];
        std::swap(mArray[1],mArray[mHeapSize]);
        mHeapSize--;
        maxHeapIFY(1);
        return max;
    }



    inline bool increaseKey(int arrayIndex,int value){
        if (arrayIndex < 1 || arrayIndex > mHeapSize || mArray[arrayIndex]  >= value){
            std::cout << "no need to increase" << std::endl;
            return false;
        }
        mArray[arrayIndex] = value;
        while(arrayIndex > 1 && mArray[arrayIndex] > mArray[parent(arrayIndex)]){
            std::swap(mArray[arrayIndex],mArray[parent(arrayIndex)]);
            arrayIndex = parent(arrayIndex);
        }
    }

};


#endif //HEAP_PRIORITYQUEUE_H
