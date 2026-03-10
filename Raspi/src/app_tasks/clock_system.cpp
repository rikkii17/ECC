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
    //アラームをCSVから読み込み
    alarm_system::get_alarm_list_from_csv();

    alarm_system_config::alarm_list* alarm_list_data = alarm_system_config::alarm_list_head;
    std::tm now_time;

    while (true){
        if(alarm_list_data != nullptr && alarm_system_config::ararm_is_ringing){
            now_time = clock_system::get_now_time();

            //アラームをならすフラッグを立てる
            if(alarm_list_data->alarm_hour == now_time.tm_hour && alarm_list_data->alarm_minute == now_time.tm_min){
                if(alarm_list_data->week_data.is_active){
                    //曜日の設定を確認
                    if((alarm_list_data->week_data.sunday && now_time.tm_wday == 0) ||
                       (alarm_list_data->week_data.monday && now_time.tm_wday == 1) ||
                       (alarm_list_data->week_data.tuesday && now_time.tm_wday == 2) ||
                       (alarm_list_data->week_data.wednesday && now_time.tm_wday == 3) ||
                       (alarm_list_data->week_data.thursday && now_time.tm_wday == 4) ||
                       (alarm_list_data->week_data.friday && now_time.tm_wday == 5) ||
                       (alarm_list_data->week_data.saturday && now_time.tm_wday == 6)){
                        alarm_system_config::ararm_is_ringing = true;
                    }
                }
            }

            //次のリストデータへアクセス
            if(alarm_list_data->next == nullptr)    alarm_list_data = alarm_system_config::alarm_list_head;
            else    alarm_list_data = alarm_list_data->next;
        }
        
        //終了操作
        if(software_config::controller::get_system_is_running() == false){
            //アラームの設定を保存
            alarm_system::save_alarm_list_to_csv();
            break;
        }
        
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

void alarm_system::get_alarm_list_from_csv(){
    try{
        csv::CSVReader reader("/var/lib/ECC_device/alarm_list.csv");
        
        for(csv::CSVRow& row : reader){
            int hour = row[0].get<int>();
            int minute = row[1].get<int>();
            alarm_system_config::week_config week_data;
            week_data.is_active = row[2].get<bool>();
            week_data.sunday = row[3].get<bool>();
            week_data.monday = row[4].get<bool>();
            week_data.tuesday = row[5].get<bool>();
            week_data.wednesday = row[6].get<bool>();
            week_data.thursday = row[7].get<bool>();
            week_data.friday = row[8].get<bool>();
            week_data.saturday = row[9].get<bool>();

            alarm_system::set_alarm_list(hour,minute,week_data);
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return;
}

void alarm_system::save_alarm_list_to_csv(){
    //CSVファイルを空にして開く
    std::ofstream file("/var/lib/ECC_device/alarm_list.csv");
    //開かないときの条件処理
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }
    //CSVへ書き込み
    alarm_system_config::alarm_list* current_alarm = alarm_system_config::alarm_list_head;
    while (current_alarm != nullptr) {
        file << current_alarm->alarm_hour << ","
             << current_alarm->alarm_minute << ","
             << static_cast<int>(current_alarm->week_data.is_active) << ","
             << static_cast<int>(current_alarm->week_data.sunday) << ","
             << static_cast<int>(current_alarm->week_data.monday) << ","
             << static_cast<int>(current_alarm->week_data.tuesday) << ","
             << static_cast<int>(current_alarm->week_data.wednesday) << ","
             << static_cast<int>(current_alarm->week_data.thursday) << ","
             << static_cast<int>(current_alarm->week_data.friday) << ","
             << static_cast<int>(current_alarm->week_data.saturday) << "\n";
        current_alarm = current_alarm->next;
    }

    file.close();
}