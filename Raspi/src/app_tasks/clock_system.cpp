#include<ctime>
//時間系のシステムを定義するため。
#include<atomic>
//安全に変数を扱う目的

#include"clock_system.hpp"
#include"clock_system_config.hpp"
#include"softconfig.hpp"

void clock_system::set_now_time(){
    while(true){
        clock_system::now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        //std::chronoによって時間を把握し、それをtime_t型に変換
        

        if(software_config::controller::get_system_is_running() == false)   break;
    }
    return;    
}

std::tm clock_system::get_now_time(){
    std::time_t now_time_t_copy = clock_system::now_time_t.load();
    std::tm* now_time = std::localtime(&now_time_t_copy);
    return(*now_time);
}

void alarm_system::check_alarm(){
    alarm_system_config::alarm_list* alarm_list_data = alarm_system_config::alarm_list_head;
    std::tm now_time;

    while (true){
        if(alarm_list_data != nullptr && alarm_system_config::ararm_is_ringing){
            now_time = clock_system::get_now_time();

            //アラームをならすフラッグを立てる
            if(alarm_list_data->alarm_hour == now_time.tm_hour && alarm_list_data->alarm_minute == now_time.tm_min) alarm_system_config::ararm_is_ringing = true;

            //次のリストデータへアクセス
            if(alarm_list_data->next == nullptr)    alarm_list_data = alarm_system_config::alarm_list_head;
            else    alarm_list_data = alarm_list_data->next;
        }
        
        //終了操作
        if(software_config::controller::get_system_is_running() == false)   break;
        
    }
    return;
}

void alarm_system::set_alarm_list(int hour,int minuts,alarm_system_config::week_config week_data){

    alarm_system_config::alarm_list* new_alarm_list = new alarm_system_config::alarm_list;

    new_alarm_list->next = nullptr;

    //それぞれコピーする。
    new_alarm_list->alarm_hour = hour;
    new_alarm_list->alarm_minute = minuts;
    new_alarm_list->week_data = week_data;

    if(alarm_system_config::alarm_list_head == nullptr){
        alarm_system_config::alarm_list_head = new_alarm_list;
        return;
    }

    alarm_system_config::alarm_list* next_list_data = alarm_system_config::alarm_list_head;
    while (next_list_data->next != nullptr) next_list_data = next_list_data->next;
    
    next_list_data->next = new_alarm_list;

    return;
}