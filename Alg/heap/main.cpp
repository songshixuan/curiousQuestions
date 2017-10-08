#include "heap.h"
#include "PriorityQueue.h"

void testHeap(){
    std::vector<int> vec {6,9,1,3,5,4,3,2,1};
    heap myHeap(vec);
    myHeap.showArray();
    myHeap.heapSort();
    myHeap.showArray();
}

void testPriQue(){
    std::vector<int> vec {6,9,1,3,5,4,3,2,1};
    MaxPriorityQueue mpq(vec);
    int max = 0;
    mpq.insertToMaxHeap(29);
    mpq.insertToMaxHeap(12);
    while (!mpq.isEmpty()){
        max = mpq.extractMax();
        std::cout << max << std::endl;


    }


}


int main(){
    testPriQue();
    return 0;
}