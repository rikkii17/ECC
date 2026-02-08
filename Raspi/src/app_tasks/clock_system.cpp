#include<ctime>
//時間系のシステムを定義するため。

#include"clock_system.hpp"
#include"hardconfig.hpp"

void clock_system::get_now_time(std::tm *now_time){
    while(true){
        time_t system_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    //std::chronoによって時間を把握し、それをtime_t型に変換
        *now_time = *std::localtime(&system_time_t);

        if(hardwere_config::controller::get_esystem_is_running() == false)   break;
    }
    return;    
}
