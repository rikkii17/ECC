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



// 起動した場合、

int main(){
    std::tm test;

    std::cout <<"Starting up the system"<<std::endl;

    // ハードウェアパッケージの初期化
    std::cout <<"\t Initializing hardware"<<std::endl;
    

    std::cout<<"Launching the application"<<std::endl;

    std::cout<<"\t starting the clock system"<<std::endl;
    std::thread system_clock_thread(clock_system::set_now_time);

    std::cout<<"\t starting the clock GUI window \n \n \n"<<std::endl;
    sf::RenderWindow clockwindow(sf::VideoMode::getDesktopMode(),"fullscreen",sf::State::Fullscreen);

    while(clockwindow.isOpen()){
        while(std::optional event = clockwindow.pollEvent()){
            std::tm now_time = clock_system::get_now_time();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) == true){
                clockwindow.close();
                softwere_config::controller::put_system_is_running(false);
            }
        }
        if(softwere_config::controller::get_system_is_running() == false)  break;
    }    

    std::cout<<"\n \n \n Shutting down system"<<std::endl;
    //終了操作
    system_clock_thread.join();

    std::cout<<"Bye"<<std::endl;
    return 0;
}