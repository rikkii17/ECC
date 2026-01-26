#include<ctime>
//時間系のシステムを定義するため。

#include"clock_system.hpp"

void clock_system::get_now_time(std::tm *now_time){
    while(true){
        time_t system_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        *now_time = *std::localtime(&system_time_t);
    }
    return;    
}
