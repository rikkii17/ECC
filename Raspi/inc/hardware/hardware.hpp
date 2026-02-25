#ifndef HARDWARE_HPP
    #define HARDWARE_HPP
    #include<string>

    #include"hardware_config.hpp"
    
    class hardware{
    public:
        class pwm{
            public:
            std::string base_path;

            //コンストラクタ
            pwm(int chip,int channnel);

            void output(int period,int duty_cycle,int enable,int polarity);
            /*
                
            */

            
        };


        static void hardware_system();
    };

#endif