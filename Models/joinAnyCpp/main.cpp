#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <unordered_map>
#include <vector>
#include "thread.h"
int main(){


    std::vector<int> workTs = {1,2,3,4,3,2,1,2,3,5,6};
    Pool p(workTs);


    return 0;
}
