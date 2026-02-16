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

    }


void hardware::hardware_system(){
    
    return;
}