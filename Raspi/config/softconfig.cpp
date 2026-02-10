#include"softconfig.hpp"
#include<atomic>

std::atomic<bool>& softwere_config::controller::get_system_is_running(){
    return softwere_config::controller::system_is_running;
}

void softwere_config::controller::put_system_is_running(bool system_flag){
    softwere_config::controller::system_is_running = system_flag;
    return;
}