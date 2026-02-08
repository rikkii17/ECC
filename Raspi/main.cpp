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

#include"hardconfig.hpp"
//ハードウェア全体に関する基本設定情報
#include"clock_system.hpp"
//時計機能を導入するためのアプリケーションライブラリ



// 起動した場合、

int main(){
    std::tm test;

    std::cout <<"システムを立ち上げています"<<std::endl;
    
    sf::RenderWindow clockwindow(sf::VideoMode::getDesktopMode(),"fullscreen",sf::State::Fullscreen);

    // ハードウェアパッケージの初期化
    std::cout <<"\t ハードウェアを初期化中"<<std::endl;
    clock_system clock_system_instance;
    
    std::cout<<"アプリケーションを立ち上げています"<<std::endl;
    std::thread system_clock_thread(&clock_system::get_now_time,&clock_system_instance,std::ref(clock_system_instance.now_time));

    while(clockwindow.isOpen()){
        if(test.tm_sec != clock_system_instance.now_time->tm_sec){
            std::cout <<clock_system_instance.now_time->tm_hour<<":"<<clock_system_instance.now_time->tm_min<<":"<<clock_system_instance.now_time->tm_sec<<hardwere_config::controller::put_system_is_running<<std::endl;   //testコード
            test = *clock_system_instance.now_time;
        }
        if(hardwere_config::controller::get_system_is_running() == false) std::cout<<"end"<<std::endl;


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) == true)   hardwere_config::controller::put_system_is_running(false);
        
        if(hardwere_config::controller::get_system_is_running() == false)  break;
    }    

    //終了操作
    system_clock_thread.join();
    return 0;
}