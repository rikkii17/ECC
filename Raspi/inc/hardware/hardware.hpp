#ifndef HARDWARE_HPP
    #define HARDWARE_HPP
    #include<string>

    #include<fcntl.h>
    //デバイスファイルを開く
    #include<unistd.h>
    //デバイス操作関数系
    #include<sys/ioctl.h>
    //速度やモードのセット関数
    #include<linux/spi/spidev.h>
    //SPI通信構造体ヘッダー

    #include"hardware_config.hpp"
    
    class hardware{
    public:
        class pwm{
            public:
            std::string base_path;

            //コンストラクタ
            pwm(int chip,int channnel);

            void set_output(int period,int duty_cycle,std::string polarity);
            /*
                第1引数:    設定周期(int)
                第2引数:    設定ON時間(int)
                第3引数:    設定極性(string)

                返り値:     void
            */
            
            void output_enable(int enable);
            /*
                規定の設定で出力を設定する関数
                第１引数:   出力の成否(int)
                返り値:     void
            */

        };
        class spi{
        private:
            int fd;
            uint32_t speed;

        public:
            spi(const std::string& device, uint32_t speed);
            /*
                コンストラクタ
                第1引数:    SPI通信Path（string)
                第2引数:    通信速度(32bit int)
            */

            ~spi();
            //デストラクタ

            int read_adc(int channel);
            /*
                SPIの値を返す関数
                第1引数:    MCP3208のチャンネル位置
                返り値:     SPIから送られてきた整数値
            */
        
            float to_voltage(int spi_data);
            /*
                SPIのデータを電圧に直す関数
                第1引数:    spiデータ（int）
                返り値:     電圧(float)
            */
        
            float weight_to_voltage(float weight);
            /*
                電圧値を重量に変える
                第1引数:    電圧(float)
                返り値:     重量(float)
            */



        };




        static void hardware_system();
    };

#endif