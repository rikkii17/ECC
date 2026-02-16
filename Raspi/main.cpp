#include<iostream>
//CLIコード用
#include<ctime>
//システム時間を取得するため
#include<thread>
//マルチスレッドでの操作用
#include<SFML/Window.hpp>
//入力・ウィンドウ系
#include<SFML/Graphics.hpp>
//映像出力
#include<atomic>
//atomic変数の利用

#include"softconfig.hpp"
//ハードウェア全体に関する基本設定情報
#include"clock_system.hpp"
//時計機能を導入するためのアプリケーションライブラリ
#include"initialization.hpp"
//初期化系の関数ライブラリ
#include<error.hpp>
//エラー関係を扱うライブラリ



int main(){
    std::cout <<"Starting up the system"<<std::endl;

    // ハードウェアパッケージの初期化
    std::cout <<"\t Initializing hardware"<<std::endl;
    int error_flag;

    error_flag = initialization::software::device();
    if(error_process::initialization_error(error_flag)) std::exit(EXIT_FAILURE);


    std::cout<<"Launching the application"<<std::endl;

    std::cout<<"\t starting the clock system"<<std::endl;
    std::thread system_clock_thread(clock_system::set_now_time);
    std::cout<<"\t startiong the alarm system"<<std::endl;
    std::thread alarm_system_thread(alarm_system::check_alarm);
    //SFMLウィンドウ立ち上げ
    std::cout<<"\t starting the clock GUI window \n \n \n"<<std::endl;
    sf::RenderWindow clockwindow(sf::VideoMode({1280,720}), "fullscreen");

    //ウィンドウループ
    while(clockwindow.isOpen()){
        while(std::optional event = clockwindow.pollEvent()){
            std::tm now_time = clock_system::get_now_time();

          //イベントハンドラ  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) == true){
                clockwindow.close();
                software_config::controller::put_system_is_running(false);
            }
        }


        //終了確認
        if(software_config::controller::get_system_is_running() == false)  break;
    }    

    std::cout<<"\n \n \nShutting down system"<<std::endl;
    //終了操作
    alarm_system_thread.join();
    std::cout<<"\talarm system shutdown"<<std::endl;
    system_clock_thread.join();
    std::cout<<"\tclock system shutdown"<<std::endl;

    std::cout<<"\n Bye"<<std::endl;
    return 0;
}