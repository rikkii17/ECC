#include<ctime>
//時間系のシステムを定義するため。
#include<atomic>
//安全に変数を扱う目的
#include<sstream>
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
        if(alarm_list_data != nullptr && !alarm_system_config::ararm_is_ringing){
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
        }   
        //次のリストデータへアクセス
        if(alarm_list_data->next == nullptr)    alarm_list_data = alarm_system_config::alarm_list_head;
        else    alarm_list_data = alarm_list_data->next;
        
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
/*
int alarm_system::select_alarm_list(){
    int select_number;
    std::string input_data;
    alarm_system_config::alarm_list alarm_list* = alarm_system_config::alarm_list_head;

    //リストの出力
    for(select_number = 1:alarm_list.next == nullptr:select_number++){
        std::cout<<select_number<<". "<<alarm_list->alarm_hour<<":"<<alarm_list->alarm_minute<<" ";
        if(alarm_list->week_data.sunday)    std::cout<<"Sun ";
        if(alarm_list->week_data.monday)    std::cout<<"Mon ";
        if(alarm_list->week_data.tuesday)   std::cout<<"Tue ";
        if(alarm_list->week_data.wednesday) std::cout<<"Wed ";
        if(alarm_list->week_data.thursday)  std::cout<<"Thu ";
        if(alarm_list->week_data.friday)    std::cout<<"Fri ";
        if(alarm_list->week_data.saturday)  std::cout<<"Sat ";
        if(alarm_list->week_data.is_active)   std::cout<<"ON";
        else    std::cout<<"OFF";
        std::cout<<std::endl;
        alarm_list = alarm_list->next;
    }
    //入力部
    std::cout<<"Prease select the alarm list number"<<std::endl;
    std::cin>>input_data;
    //値を読み込む
    try{
        select_number = std::stoi(input_data);
    }
    catch(const std::exception& e){
        std::cerr << "Invalid input. Please enter a valid number." << std::endl;
        return -1;
    }   
    return(select_number-1);
}
実装していないためコメントアウト    
*/

void alarm_system::set_new_alarm(){
    std::string input_data;
    int hour = 0;
    int minute  = 0;
    char delimiter;

    //時間の取得
    std::cout<<"setting the new alarm"<<std::endl;
    std::cout<<"Please enter the alarm time\nex)08:30 "<<std::endl;
    std::cin>>input_data;

    //時間の入力値の解析
    std::stringstream ss(input_data);
    ss >> hour >> delimiter >> minute;
        if (ss.fail() || delimiter != ':' || hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            std::cerr << "Invalid time format. Please enter in HH:MM format." << std::endl;
            return;
        }
    //曜日の取得
    std::cout<<"Please enter the day of the week you wish to use as a number"<<std::endl;
    std::cout<<"0: Sunday\n1: Monday\n2: Tuesday\n3: Wednesday\n4: Thursday\n5: Friday\n6: Saturday"<<std::endl;
    std::cout<<"ex) If you want to set an alarm for Monday, Wednesday, and Friday, enter 1010101"<<std::endl;
    std::cin>>input_data;
    if(input_data.length() != 7){
        std::cerr << "Invalid input. Please enter a 7-digit binary string." << std::endl;
        return;
    }
    //曜日の設定の解析
    alarm_system_config::week_config week_data;
    week_data.is_active = 1;
    week_data.sunday = input_data[0] - '0';
    week_data.monday = input_data[1] - '0';
    week_data.tuesday = input_data[2] - '0';
    week_data.wednesday = input_data[3] - '0';
    week_data.thursday = input_data[4] - '0';
    week_data.friday = input_data[5] - '0';
    week_data.saturday = input_data[6] - '0';

    //データをアラームリストへ追加
    alarm_system::set_alarm_list(hour,minute,week_data);

    return;
}
/*
void alarm_system::edit_alarm(){
    int select_number;
    while (true){
        std::cout<<"Edhit the alarm list ON/OFF"<<std::endl;
        select_number = alarm_system::select_alarm_list();
        if(select_number < 0){
            std::cerr << "Invalid selection. Please try again." << std::endl;
            continue;
        }
        alarm_system_config::alarm_list* current_alarm = alarm_system_config::alarm_list_head;
        for(int i = 0; i < select_number; i++){
            if(current_alarm->next == nullptr){
                std::cerr << "Selected number exceeds the alarm list." << std::endl;
                return;
            }
            current_alarm = current_alarm->next;
        }

    }

}
未実装コードのためコメントアウト    
*/