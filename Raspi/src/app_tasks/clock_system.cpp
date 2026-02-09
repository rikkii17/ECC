#include<ctime>
//時間系のシステムを定義するため。
#include<atomic>


#include"clock_system.hpp"
#include"hardconfig.hpp"

void clock_system::set_now_time(){
    while(true){
        clock_system::now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        //std::chronoによって時間を把握し、それをtime_t型に変換
        

        if(hardwere_config::controller::get_system_is_running() == false)   break;
    }
    return;    
}

std::tm clock_system::get_now_time(){
    std::time_t now_time_t_copy = clock_system::now_time_t.load();
    std::tm* now_time = std::localtime(&now_time_t_copy);
    return(*now_time);
}
