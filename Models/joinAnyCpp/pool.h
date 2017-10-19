#include <vector>
#include <thread>
#include <unordered_map>
enum TS_State{RUN,TERM,JOIN};
class Pool{
    public:
        typedef std::thread::id tid;
        Pool(const std::unordered_map<tid,TS_State>& val);
        Pool();

    private:
        std::unordered_map<tid,TS_State> mTid2Stat;


};
