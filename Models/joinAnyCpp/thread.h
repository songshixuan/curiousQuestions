#include <thread>
#include <string>
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <vector>
enum TS_STATE{RUNNING,TERM,JOINED};
struct Thread{
    std::thread::id mTid;
    std::condition_variable* mCv;
    std::thread* mTPtr;
    TS_STATE mStat;
    std::mutex* mMut;

    inline Thread(int i,std::mutex* mtx,std::condition_variable* cv):mCv(cv),mMut(mtx){
        mTPtr = new std::thread(simpleWork,i,this);
        mTid = mTPtr->get_id();
        mStat = TS_STATE::RUNNING;
    }
    inline static void simpleWork(int i,Thread* t){

        std::cout << "thread" << t->mTid << "raised" << std::endl;
        t->mMut->lock();
        std::this_thread::sleep_for (std::chrono::seconds(i));
        std::cout << "thread" << t->mTid << " terminated" << std::endl;
        t->mStat = TS_STATE::TERM;
        t->mCv->notify_one();
        t->mMut->unlock();

    }
};


struct Pool{
    virtual ~Pool(){
        delete mCv;
        delete mMut;
        mCv =  nullptr;
        mMut = nullptr;
        for(auto m:mTs){
            delete m;
            m = nullptr;
        }
    }
    Pool(const std::vector<int>& vec):mUnjoined(0){
        mMut = new std::mutex();
        mCv = new std::condition_variable();
        for(auto m:vec){
            Thread *t = new Thread(m,mMut,mCv);
            mTs.push_back(t);
            mUnjoined++;
        }

        while(mUnjoined > 0){
            std::unique_lock<std::mutex> uLock(*mMut);
            auto msg = "reminding threads="+ std::to_string(mUnjoined) ;
            std::cout << msg << std::endl;
            while(!hasUnjoined()){
               mCv->wait(uLock);
            }

            for(int i=0;i < mTs.size();++i){
                if(mTs[i]->mStat == TS_STATE::TERM){
                   mTs[i]->mTPtr->join();
                   std::cout << "joined " << mTs[i]->mTid << std::endl;
                   mTs[i]->mStat = TS_STATE::JOINED;
                   mUnjoined--;
                }
            }
        }

    }

    bool hasUnjoined(){
        for(auto m:mTs){
            if(m->mStat == TS_STATE::TERM){
                return true;
            }
        }
        return false;
    }


    int mUnjoined;
    std::condition_variable* mCv;
    std::vector<Thread*> mTs;
    std::mutex* mMut;
};
