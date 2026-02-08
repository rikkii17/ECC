#include"hardconfig.hpp"
#include<atomic>

std::atomic<bool>& hardwere_config::controller::get_esystem_is_running(){
    return hardwere_config::controller::system_is_running;
}