#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <unordered_map>
#include "pool.h"
void work(int i,std::condition_variable* cv){
    std::this_thread::sleep_for (std::chrono::seconds(i));
}


std::unordered_map<std::thread::id,TS_State> createThreads(const std::vector<int> ts,
        std::condition_variable* cv){
    std::unordered_map<std::thread::id,TS_State> tMap;
    for(auto m:ts){
        std::thread t(work,m,cv);
        tMap[t.get_id()] = TS_State::RUN;
    }

    return tMap;
}


int main(){

    std::condition_variable cond;

    std::vector<int> workTs = {1,3,5,6,4,2,10};
    auto tMap = createThreads(workTs,&cond);


    return 0;
}
