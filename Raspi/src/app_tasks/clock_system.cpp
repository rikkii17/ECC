#include<ctime>
//時間系のシステムを定義するため。
#include<atomic>
//安全に変数を扱う目的
#include"csv.hpp"
//csvparserを扱うライブラリ

#include"clock_system.hpp"
#include"clock_system_config.hpp"
#include"softconfig.hpp"

//clock_systemクラス
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


//alarm_systemクラス
void alarm_system::check_alarm(){
    alarm_system_config::alarm_list* alarm_list_data = alarm_system_config::alarm_list_head;
    std::tm now_time;

    while (true){
        if(alarm_list_data != nullptr && alarm_system_config::ararm_is_ringing){
            now_time = clock_system::get_now_time();

            //アラームをならすフラッグを立てる
            //アラームの曜日の設定はまだ
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
    alarm_system_config::alarm_list* new_alarm = new alarm_system_config::alarm_list;
    //値の新規代入
    new_alarm->alarm_hour = hour;
    new_alarm->alarm_minute = minuts;
    new_alarm->week_data = week_data;
    new_alarm->next = nullptr;

    //アラームリストの実態が存在しない場合の処理
    if(alarm_system_config::alarm_list_head == nullptr){
        alarm_system_config::alarm_list_head = new_alarm;
    }
    //実態が存在する場合
    else{
        alarm_system_config::alarm_list* current_alarm = alarm_system_config::alarm_list_head;
        while(current_alarm->next != nullptr){
            current_alarm = current_alarm->next;
        }
        current_alarm->next = new_alarm;
    }
    return;
}

