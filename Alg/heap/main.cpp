#include "heap.h"





int main(){
    std::vector<int> vec {6,9,1,3,5,4,3,2,1};
    heap myHeap(vec);
    myHeap.showArray();
    myHeap.heapSort();
    myHeap.showArray();
    return 0;
}