#include"softconfig.hpp"
#include<atomic>

std::atomic<bool>& software_config::controller::get_system_is_running(){
    return software_config::controller::system_is_running;
}

void software_config::controller::put_system_is_running(bool system_flag){
    software_config::controller::system_is_running = system_flag;
    return;
}
