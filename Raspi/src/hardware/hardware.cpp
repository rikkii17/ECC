#include<gpiod.hpp>
#include<string>
#include<iostream>
#include<fstream>

#include"hardware.hpp"
#include"clock_system.hpp"
#include"clock_system_config.hpp"
#include"hardware_config.hpp"
#include"error.hpp"

hardware::pwm::pwm(int chip,int channel)
    : base_path("sys/class/pwm/pwmchip" + std::to_string(chip) + "/pwm" + std::to_string(channel) + "/")
    {
        std::ofstream export_file("/sys/class/pwm/pwmchip" + std::to_string(chip) + "/export");
        if(export_file.is_open()){
            export_file<<channel;
            //チャンネル番号のかきこみ
        }
        else{
            std::cerr<<"Error:The channel was not secured"<<std::endl;
        }
    }

void hardware::pwm::set_output(int period,int duty_cycle,int polarity){
    //それぞれのファイル変数の定義
    std::ofstream period_file(base_path+"pariod");
    std::ofstream duty_cycle_file(base_path+"duty_cycle");
    std::ofstream polarity_file(base_path+"polarity");

    //周期設定
    if(!period_file.is_open()){
        std::cerr<<"error:system file is not open (period)"<<std::endl;
        error_flag::hardware_pwm_error = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        return;
    }
    period_file<<std::to_string(period);
    period_file.close();
    //ON時間設定
    if(!duty_cycle_file.is_open()){
        std::cerr<<"error:system file is not open (period)"<<std::endl;
        error_flag::hardware_pwm_error = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        return;
    }
    duty_cycle_file<<std::to_string(duty_cycle);
    duty_cycle_file.close();
    //極性設定
    if(!polarity_file.is_open()){
        std::cerr<<"error:system file is not open (period)"<<std::endl;
        error_flag::hardware_pwm_error = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        return;
    }
    polarity_file<<std::to_string(polarity);
    polarity_file.close();
    
    return;
}



void hardware::hardware_system(){
     
    return;

}