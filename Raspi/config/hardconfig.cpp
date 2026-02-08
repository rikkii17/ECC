#include"hardconfig.hpp"
#include<atomic>

std::atomic<bool>& hardwere_config::controller::get_system_is_running(){
    return hardwere_config::controller::system_is_running;
}

void hardwere_config::controller::put_system_is_running(bool system_flag){
    hardwere_config::controller::system_is_running = system_flag;
    return;
}