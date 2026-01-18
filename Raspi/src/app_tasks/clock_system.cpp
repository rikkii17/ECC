#include<ctime>
//時間系のシステムを定義するため。

#include"clock_system.hpp"

void clock_system::get_now_time(time_t *now_time){
    while (true){
        std::chrono::system_clock::time_point system_now_time = std::chrono::system_clock::now();
        now_time = std::chrono::system_clock::to_time_t(system_now_time);
        return;
    }    
}
