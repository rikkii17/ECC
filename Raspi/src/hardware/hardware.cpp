#include<gpiod.hpp>
#include<string>
#include<iostream>
#include<fstream>
#include<thread>
#include<cstring>
#include<cerrno>
#include<cmath>

#include"hardware.hpp"
#include"clock_system.hpp"
#include"clock_system_config.hpp"
#include"hardware_config.hpp"
#include"error.hpp"

//PWM
hardware::pwm::pwm(int chip,int channel)
    : base_path("/sys/class/pwm/pwmchip" + std::to_string(chip) + "/pwm" + std::to_string(channel) + "/")
    {
        std::ofstream export_file("/sys/class/pwm/pwmchip" + std::to_string(chip) + "/export");
        if(export_file.is_open()){
            export_file<<channel;
            //チャンネル番号のかきこみ
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
        else{
            std::cerr<<"Error:The channel was not secured"<<std::endl;
        }
    }

void hardware::pwm::set_output(int period,int duty_cycle,std::string polarity){
    //それぞれのファイル変数の定義
    std::ofstream period_file(base_path+"period");
    std::ofstream duty_cycle_file(base_path+"duty_cycle");
    std::ofstream polarity_file(base_path+"polarity");
    bool error_flag[4];

    //周期設定
    if(!period_file.is_open()){
        std::cerr<<"error:system file is not open (period):"<<strerror(errno)<<std::endl;
        error_flag::hardware_pwm_error = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        return;
    }
    period_file<<std::to_string(period);
    period_file.close();
    //ON時間設定
    if(!duty_cycle_file.is_open()){
        std::cerr<<"error:system file is not open (duty cycle):"<<strerror(errno)<<std::endl;
        error_flag::hardware_pwm_error = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        return;
    }
    duty_cycle_file<<std::to_string(duty_cycle);
    duty_cycle_file.close();
    //極性設定
    if(!polarity_file.is_open()){
        std::cerr<<"error:system file is not open (polarity):"<<strerror(errno)<<std::endl;
        error_flag::hardware_pwm_error = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        return;
    }
    polarity_file<<polarity;
    polarity_file.close();
    
    return;
}

int hardware::pwm::output_enable(int enable){
    std::ofstream enable_file(base_path+"enable");
    if(!enable_file.is_open()){
        std::cerr<<"error:system file is not open (enable):"<<strerror(errno)<<std::endl;
        error_flag::hardware_pwm_error = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        return(error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN);
    }
    enable_file<<std::to_string(enable);
    enable_file.close();
    return(error_number::hardware::OK);
}

//SPI
hardware::spi::spi(const std::string& device, uint32_t speed) : speed(speed) {
    fd = open(device.c_str(), O_RDWR);
    if (fd < 0) {
        std::cerr << "Error: SPI device is not use." << std::endl;
        error_flag::hardware_spi_error = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        return;
    }

    uint8_t mode = SPI_MODE_0;
    uint8_t bits = 8;
    ioctl(fd, SPI_IOC_WR_MODE, &mode);
    ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
}

hardware::spi::spi::~spi() {
    if (fd >= 0) close(fd);
}

int hardware::spi::read_adc(int channel) {
    if (fd < 0) return -1;

    uint8_t tx[3] = {0};
    // MCP3208の制御ビットを設定（3bits）
    tx[0] = 0x06 | ((channel & 0x04) >> 2);
    //スタートビットとSGLの設定　測定チャンネルの設定（D2）
    tx[1] = (channel & 0x03) << 6;
    //測定チャンネルの設定（D1、D0）
    tx[2] = 0x00;
    //enpty

    uint8_t rx[3] = {0};
    //受信用バッファ
    struct spi_ioc_transfer tr = {0};
    tr.tx_buf = (unsigned long)tx;
    tr.rx_buf = (unsigned long)rx;
    tr.len = 3;
    tr.speed_hz = speed;
    tr.bits_per_word = 8;
    //通信設定用構造体とその設定

    if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 1) {
        return -1;
    }

    return ((rx[1] & 0x0F) << 8) | rx[2];
}

float  hardware::spi::to_voltage(int spi_data){
    return((spi_data*3.3)/4095.0);
}

float hardware::spi::weight_to_voltage(float weight){
    return(3.3*std::exp(0.3*weight));
    //0.3=exp(zeta*m)のzetaが0.3くらいであると推測

}

void hardware::hardware_system(){
    hardware::pwm alarm(0,0);
    //チップナンバー、チャンネルナンバー
    alarm.set_output(10000,10000,"normal");
    int error_flag = error_number::hardware::OK;
    while(true){
        float weight_voltage;
        hardware::spi weight_data_spi(hardware_config::spi_device,hardware_config::spi_speed);

        weight_voltage = weight_data_spi.read_adc(0);
        if(weight_voltage <0)error_flag = error_number::hardware::HARDWARE_FILE_IS_NOT_OPEN;
        //testcode
        if(alarm_system_config::ararm_is_ringing){
            if(1<weight_voltage){//電圧閾値を試しに1Vに設定

                if(error_flag == error_number::hardware::OK){
                    error_flag = alarm.output_enable(1);

                    //おそらくこの辺がおかしい（while true ERROR
                }
            }
        }
        else{
            alarm.output_enable(0);
        }
        //終了操作
        if(software_config::controller::get_system_is_running() == false){
            weight_data_spi.~spi();
            break;
        }
    }
    return;
}