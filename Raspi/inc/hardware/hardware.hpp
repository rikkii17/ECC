#ifndef HARDWARE_HPP
    #define HARDWARE_HPP
    #include<string>
    
    class hardware{
    public:
        class pwm{
            public:
            std::string base_path;

            //コンストラクタ
            pwm(int chip,int channnel);

            void set_params()
        };
    };

#endif