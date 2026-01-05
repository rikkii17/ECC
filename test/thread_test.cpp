#include<iostream>
#include<thread>

void thread_function(){
    std::cout<<"threadtask"<<std::endl;
    return;
}

int main(){
    std::thread threadtask(thread_function);
    std::cout<<"main task"<<std::endl;

    threadtask.join();
    std::cout<<"end program"<<std::endl;

    return 0;
}