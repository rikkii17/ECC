#include<iostream>
//CLIコード用
#include<ctime>
//システム時間を取得するため
#include<thread>
//マルチスレッドでの操作用

#include"inc/app_tasks/clock_system.hpp"
//時計機能を導入するためのアプリケーションライブラリ



// 起動した場合、

int main(){
    std::cout <<"システムを立ち上げています"<<std::endl;


    // ハードウェアパッケージの初期化
    std::cout <<"\t ハードウェアを初期化中"<<std::endl;

    clock_system clock_system_instance;
    
    std::thread system_clock_thread(&clock_system::get_now_time,&clock_system_instance,std::ref(clock_system_instance.now_time));
    while(true){
        std::cout <<clock_system_instance.now_time->tm_hour<<clock_system_instance.now_time->tm_min<<clock_system_instance.now_time->tm_sec<<std::endl;
    }    
    return 0;
}