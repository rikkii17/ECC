#include<chrono>
#include<iostream>
#include<ctime>

int main();

int main(){    
    std::time_t now_time;
    std::chrono::system_clock::time_point system_now_time=std::chrono::system_clock::now();
    now_time = std::chrono::system_clock::to_time_t(system_now_time);
    std::cout << std::ctime(&now_time);
    return 0;
}