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

            void set_output(int period,int duty_cycle,int polarity);
            /*
                第1引数:    設定周期(int)
                第2引数:    設定ON時間(int)
                第3引数:    設定極性(int)

                返り値:     void
            */
            
            void output_enable(int enable);

        };


        static void hardware_system();
    };

#endif