#include "pool.h"


Pool::Pool():mTid2Stat(){

}

Pool::Pool(const std::unordered_map<tid,TS_State>& val):mTid2Stat(val){


}
