#include<gpiod.hpp>
#include<string>
#include<iostream>
#include<fstream>

#include"hardware.hpp"
#include"clock_system.hpp"
#include"clock_system_config.hpp"
#include"hardware_config.hpp"

hardware::pwm::pwm(int chip,int channel)
    : base_path("sys/class/pwm/pwmchip" + std::to_string(chip) + "/pwm" + std::to_string(channel) + "/")
    {
        std::ofstream export_file("/sys/class/pwm/pwmchip" + std::to_string(chip) + "/export");
        if(export_file.is_open()){
            export_file<<channel;
            //ƒ`ƒƒƒ“ƒlƒ‹”Ô†‚Ì‚©‚«‚±‚Ý
        }
        else{
            std::cerr<<"Error:The channel was not secured"<<std::endl;
        }
    }

void hardware::pwm::output(int period,int duty_cycle,int enable,int polarity){
    std::ofstream period_file(base_path+"pariod");

    return;
}


void hardware::hardware_system(){
     
    return;

}